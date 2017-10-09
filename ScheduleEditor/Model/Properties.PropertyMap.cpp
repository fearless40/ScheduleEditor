#include "pch.h"

#include <memory>

#include "Model.h"
#include "Properties.h"
#include "Properties.PropertyMap.h"

using namespace Model::Properties;


void Model::Properties::PropertyMap::add(PropertyIndex key, Property prop)
{
	mMap[key] = prop;
}

void Model::Properties::PropertyMap::remove(PropertyIndex key)
{
	mMap.erase(key);
}

