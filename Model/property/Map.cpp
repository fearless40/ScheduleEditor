#include "pch.h"

#include <memory>
#include <algorithm>
#include <sstream>
#include "model.h"
#include "Properties.h"
#include "Properties.PropertyMap.h"

using namespace model::Properties;


void model::Properties::PropertyMap::insert(KeyConst key, Property prop)
{
	if (auto item = find(key); item != mMap.end()) {
		item->value = std::move(prop);
	}
	else {
		mMap.emplace_back( Key{key}, std::move(prop) );
	}
}

void model::Properties::PropertyMap::erase(KeyConst key)
{
	if (auto item = find(key); item != mMap.end()) {
		mMap.erase(item);
	}
}

bool model::Properties::PropertyMap::has(KeyConst key) const noexcept
{
	return find(key) != mMap.end();
}

PropertyMap::PMap::iterator PropertyMap::find(KeyConst key) noexcept
{
	return std::find(mMap.begin(), mMap.end(), key);
}

PropertyMap::const_iterator PropertyMap::find(KeyConst key) const noexcept
{
	return std::find(mMap.begin(), mMap.end(), key);
}

Property & model::Properties::PropertyMap::operator[](KeyConst key) 
{
	if (auto item = find(key); item != mMap.end()) {
		return item->value;
	}
	throw "Unable to find key";
}

const Property & model::Properties::PropertyMap::operator[](KeyConst key) const
{
	if (auto item = find(key); item != mMap.end()) {
		return item->value;
	}
	throw "Unable to find key";
}

model::string model::Properties::PropertyMap::asString(KeyConst key) const
{
	if (auto item = find(key); item != mMap.end()) {
		return PropertyAsString(item->value);
	}
	return {};
}

model::string model::Properties::PropertyMap::asString(KeyConst key, model::string_view default_value) const
{
	if (auto item = find(key); item != mMap.end()) {
		return PropertyAsString(item->value);
	}
	else {
		return model::string{ default_value };
	}
}
