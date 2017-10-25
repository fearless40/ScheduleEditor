#pragma once

#include <memory>
#include "Properties.h"
#include "Model.h"

namespace Model::Properties {
	class PropertyMap {
	public:

		struct KeyValue {
			Key key;
			Property value;

			template< typename PropertyIndexType >
			friend bool operator == (const KeyValue & kv, PropertyIndexType pi) {
				return kv.key == pi;
			}

			template< typename PropertyIndexType >
			friend bool operator == (PropertyIndexType pi, const KeyValue & kv ) {
				return kv.key == pi;
			}

			template< typename PropertyIndexType >
			friend bool operator < (const KeyValue & kv, PropertyIndexType pi) {
				return kv.key < pi;
			}

			template< typename PropertyIndexType >
			friend bool operator < (PropertyIndexType pi, const KeyValue & kv) {
				return  pi < kv.key;
			}

		};

		// Most property maps will have few properties < 10. A vector linear search will be fast enough for this
		using PMap = std::vector<KeyValue>;
		using iterator = PMap::iterator;
		using const_iterator = PMap::const_iterator;

	
		// Special constructor to allow a default value to be set for the first item
		// Needed for efficent construction of Resources.
		// Otherwise not used
		template <typename ValueType>
		PropertyMap(KeyConst key, ValueType value) {
			mMap.push_back({ Key{key}, Property{value} });
		}

		PropertyMap() = default;
		PropertyMap(const PropertyMap & map) = default;
		PropertyMap(PropertyMap && map) = default;
		~PropertyMap() = default;
		
		PropertyMap & operator = (const PropertyMap & map) = default;
		PropertyMap & operator = (PropertyMap && map) = default;

		auto begin() const noexcept { return mMap.cbegin(); }
		auto end() const noexcept { return mMap.cend(); }
		auto begin() noexcept { return mMap.begin(); }
		auto end() noexcept { return mMap.end(); }

		auto size() const noexcept { return mMap.size(); }
		
		bool has(KeyConst key) const noexcept;
		PMap::iterator find(KeyConst key) noexcept;
		PMap::const_iterator find(KeyConst key) const noexcept;
		Property & operator [] (KeyConst key);
		const Property & operator [] (KeyConst key) const;

		// Converts it
		Model::string asString(KeyConst key) const;
		Model::string asString(KeyConst key, Model::string_view default_value) const;


		template<typename Value> 
		Value as(KeyConst key) {
			if (auto found = find(key); found != mMap.end()) {
				return std::get<Value>(*found);
			}
			return {};
		}

		template<typename Value>
		Value as(KeyConst key, Value default_value) {
			if (auto found = find(key); found != mMap.end()) {
				return std::get<Value>(found->value);
			}
			return default_value;
		}

		Model::string as(KeyConst key, Model::string_view default_value) {
			if (auto found = find(key); found != mMap.end()) {
				return std::get<Model::string>(found->value);
			}
			return Model::string{ default_value };
		}

		void insert(KeyConst key, Property prop);

		template <typename ValueType> 
		void insert(KeyConst key, ValueType vt) {
			insert(key, Property{ vt });
		}
		
		void erase(KeyConst key);


	protected:
		PMap mMap;

	};

	using PropertyMapUniquePtr = std::unique_ptr<PropertyMap>;

}