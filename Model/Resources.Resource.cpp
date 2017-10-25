#include "pch.h"
#include <sstream>
#include <variant>
#include "Resources.Resource.h"

using namespace Model::Resources;

Resource::Resource(const ResourceType & owner, ResourceID id) :
	mType{ owner },
	mId{id},
	PropertyMap(default_key, default_value_value )
{
}

Model::Resources::Resource::Resource(const ResourceType & owner, ResourceID id, PropertyMap && pmap) :
	mType{ owner },
	mId{ id },
	PropertyMap{std::move(pmap)}
{
}
