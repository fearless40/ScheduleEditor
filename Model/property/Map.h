#pragma once

#include <memory>
#include "Property.h"
#include "../model.h"

namespace model::property {
	class Map {
	public:

		struct KeyValue {
			Key key;
			Property value;

			KeyValue(Key k, Property v) : key{ k }, value{ v } {}
			//KeyValue(Key k, Property && v) : key{ k }, value{ std::move(v) } {}

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
		Map(KeyConst key, ValueType value) {
			mMap.push_back({ Key{key}, Property{value} });
		}

		Map() = default;
		Map(const Map & map) = default;
		Map(Map && map) = default;
		~Map() = default;
		
		Map & operator = (const Map & map) = default;
		Map & operator = (Map && map) = default;

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
		model::string asString(KeyConst key) const;
		model::string asString(KeyConst key, model::string_view default_value) const;


		template<typename Value> 
		Value as(KeyConst key) {
			if (auto found = find(key); found != mMap.end()) {
				return std::get<Value>(found->value);
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

		model::string as(KeyConst key, model::string_view default_value) {
			if (auto found = find(key); found != mMap.end()) {
				return std::get<model::string>(found->value);
			}
			return model::string{ default_value };
		}

		void insert(KeyConst key, Property prop);

		template <typename ValueType> 
		void insert(KeyConst key, ValueType vt) {
			insert(key, Property{ vt });
		}
		
		/*template <>
		void insert(KeyConst key, const wchar_t * vt) {
			insert(key, Property{ std::move(model::string{vt}) });
		}*/
		
		void erase(KeyConst key);


	protected:
		PMap mMap;

	};


}