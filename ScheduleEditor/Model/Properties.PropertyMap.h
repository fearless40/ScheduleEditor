#pragma once

#include "Properties.h"

namespace Model::Properties {
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

}