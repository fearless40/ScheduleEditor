#pragma once

#include <unordered_map>
#include "Properties.h"

namespace Model::Properties {
	class PropertyMap {
	public:
		using PMap = std::unordered_map<Model::Index, Property>;

		PropertyMap();
		PropertyMap(PropertyMap & map);
		PropertyMap(PropertyMap && map);
		~PropertyMap();

		void add(PropertyIndex key, Property prop);
		void remove(PropertyIndex key);

		auto begin() const {
			return mMap.cbegin();
		}

		auto end() const {
			return mMap.cend();
		}

		auto begin() {
			return mMap.begin();
		}

		auto end() {
			return mMap.end();
		}

		bool has(PropertyIndex key) const {
			return (mMap.find(key) != mMap.end());
		}

		// Will throw an exception if no value exists
		template< typename T >
		T get(PropertyIndex key) const {
			auto value = mMap.at(key);
			return std::get<T>(value);
		}

		// If it can't find the value will return the default value specifie by the user
		template< typename T >
		T get(PropertyIndex key, T defValue) const {
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