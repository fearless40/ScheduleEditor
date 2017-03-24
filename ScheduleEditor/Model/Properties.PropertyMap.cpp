#include "pch.h"

#include <memory>

#include "Model.h"
#include "Properties.h"
#include "Properties.PropertyMap.h"

using namespace Model::Properties;

PropertyMap::PropertyMap()
{
}

Model::Properties::PropertyMap::PropertyMap(PropertyMap & map) : mMap(map.mMap)
{
	
}

Model::Properties::PropertyMap::PropertyMap(PropertyMap && map) : mMap(std::move(map.mMap)) 
{
	
}


PropertyMap::~PropertyMap()
{
}

void Model::Properties::PropertyMap::add(Model::Index key, Property prop)
{
	mMap[key] = prop;
}

void Model::Properties::PropertyMap::remove(Model::Index key)
{
	mMap.erase(key);
}

