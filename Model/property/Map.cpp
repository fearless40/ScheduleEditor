#include "pch.h"

#include <memory>
#include <algorithm>
#include <sstream>
#include "model.h"
#include "Property.h"
#include "Map.h"

using namespace model::property;


void Map::insert(KeyConst key, Property prop)
{
	if (auto item = find(key); item != mMap.end()) {
		item->value = std::move(prop);
	}
	else {
		mMap.emplace_back( Key{key}, std::move(prop) );
	}
}

void Map::erase(KeyConst key)
{
	if (auto item = find(key); item != mMap.end()) {
		mMap.erase(item);
	}
}

bool Map::has(KeyConst key) const noexcept
{
	return find(key) != mMap.end();
}

Map::iterator Map::find(KeyConst key) noexcept
{
	return std::find(mMap.begin(), mMap.end(), key);
}

Map::const_iterator Map::find(KeyConst key) const noexcept
{
	return std::find(mMap.begin(), mMap.end(), key);
}

Property & Map::operator[](KeyConst key)
{
	if (auto item = find(key); item != mMap.end()) {
		return item->value;
	}
	throw "Unable to find key";
}

const Property & Map::operator[](KeyConst key) const
{
	if (auto item = find(key); item != mMap.end()) {
		return item->value;
	}
	throw "Unable to find key";
}

model::string Map::asString(KeyConst key) const
{
	if (auto item = find(key); item != mMap.end()) {
		return PropertyAsString(item->value);
	}
	return {};
}

model::string Map::asString(KeyConst key, model::string_view default_value) const
{
	if (auto item = find(key); item != mMap.end()) {
		return PropertyAsString(item->value);
	}
	else {
		return model::string{ default_value };
	}
}
