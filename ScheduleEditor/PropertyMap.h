#pragma once

namespace Model {
	namespace Properties {
		using Property = std::variant<long, double, bool, std::string>;
		using RangeProperty = std::variant<long, double>;

		enum class ValueTypes {
			vtLONG,
			vtBOOL,
			vtDOUBLE,
			vtSTRING
		};

		struct PropertyDefinition {
			std::string		name;
			bool			mandatory;
			ValueTypes		type;
			Property		defvalue;
			RangeProperty	min;
			RangeProperty	max;
		};

		class PropertyMap;
		class PropertyTemplate;

		// Static Functions
		PropertyTemplate * CreateTemplate(std::string templateid);
		PropertyMap		 CreateMap(std::string templateid);
		PropertyMap		 CreateMap(PropertyTemplate * temp);

		const PropertyTemplate * FindTemplate(std::string templateid);


		// Classes
		class PropertyMap {
		public:
			using PMap = std::unordered_map<std::string, Property>;

			void add(std::string key, Property prop);
			void remove(std::string key);

			auto begin() -> decltype(mMap.cbegin()) const {
				return mMap.cbegin();
			}

			auto end() -> decltype(mMap.cend()) const {
				return mMap.cend();
			}

			bool has(std::string key) {
				return (mMap.find(key) != mMap.end());
			}

			// Will throw an exception if no value exists
			template< typename T >
			T get(std::string key) const {
				auto value = mMap.at(key);
				return std::get<T>(value);
			}

			// If it can't find the value will return the default value specifie by the user
			template< typename T >
			T get(std::string key, T defValue) const {
				auto found = mMap.find(key);
				if (found != mMap.end()) {
					return std::get<T>(*found);
				}
				else {
					return defValue;
				}
			}



		protected:
			PMap mMap;
			
		};

		class PropertyTemplate {
		public:
			using PropertyDefinitions = std::vector<PropertyDefinition>;

			void addString(std::string name, std::string defaultvalue, bool mandatory = false);
			void addLong(std::string name, long defaultvalue, long min, long max, bool mandatory = false);
			void addDouble(std::string name, double defaultvalue, double min, double max, bool mandatory = false);
			void addBool(std::string name, bool defaultvalue, bool mandatory = false);



		private:

			PropertyDefinitions mDefinitions;

			// Used to look it up 
			Index mIndex;
		};
	}
}