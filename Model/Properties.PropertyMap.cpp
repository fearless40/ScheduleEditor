#include "pch.h"

#include <memory>
#include <algorithm>
#include <sstream>
#include "Model.h"
#include "Properties.h"
#include "Properties.PropertyMap.h"

using namespace Model::Properties;


void Model::Properties::PropertyMap::insert(KeyConst key, Property prop)
{
	if (auto item = find(key); item != mMap.end()) {
		item->value = prop;
	}
	else {
		mMap.push_back({ Key{key}, prop });
	}
}

void Model::Properties::PropertyMap::erase(KeyConst key)
{
	if (auto item = find(key); item != mMap.end()) {
		mMap.erase(item);
	}
}

bool Model::Properties::PropertyMap::has(KeyConst key) const noexcept
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

Property & Model::Properties::PropertyMap::operator[](KeyConst key) 
{
	if (auto item = find(key); item != mMap.end()) {
		return item->value;
	}
	throw "Unable to find key";
}

const Property & Model::Properties::PropertyMap::operator[](KeyConst key) const
{
	if (auto item = find(key); item != mMap.end()) {
		return item->value;
	}
	throw "Unable to find key";
}

Model::string Model::Properties::PropertyMap::asString(KeyConst key) const
{
	if (auto item = find(key); item != mMap.end()) {
		return PropertyAsString(item->value);
	}
	return {};
}

Model::string Model::Properties::PropertyMap::asString(KeyConst key, Model::string_view default_value) const
{
	if (auto item = find(key); item != mMap.end()) {
		return PropertyAsString(item->value);
	}
	else {
		return Model::string{ default_value };
	}
}
