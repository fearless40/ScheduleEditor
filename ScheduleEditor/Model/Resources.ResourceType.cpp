#include "pch.h"
#include <memory>
#include <algorithm>

#include "Model.h"
#include "ModelIndex.h"
#include "Properties.PropertyTemplate.h"
#include "Resources.Resource.h"
#include "Resources.ResourceType.h"



using namespace Model;
using namespace Resources;

//ModelIndex<ResourceType> ResourceTypeOwner;

Resource & Model::Resources::ResourceType::create()
{
	auto res = std::make_unique<Resource>(*this, getNextID() );
	mItems.push_back(std::move(res));
	return *mItems.back();
}

Resource & Model::Resources::ResourceType::create(const Model::Properties::PropertyMap & map)
{
	auto res = std::make_unique<Resource>(*this, getNextID(), map);
	mItems.push_back(std::move(res));
	return *mItems.back();
}

void Model::Resources::ResourceType::remove(const Resource & r)
{
	if (&(r.getType()) != this) {
		return;
	}

	auto res = std::find_if(mItems.begin(), mItems.end(), [&](const auto & v) {
		if (v->getId() == r.getId()) {
			return true;
		}
		else {
			return false;
		}
	});

	if (res != mItems.end()) {
		mItems.erase(res);
	}
}

const Model::Properties::PropertyTemplate & Model::Resources::ResourceType::propertyTemplate() const
{
	if (mPropTemp) {
		return *mPropTemp;
	}
	else {
		return Properties::PropertyTemplateOwner.Find(NullIndex);
	}
}

ResourceType::ResourceType()
{
}

ResourceID Model::Resources::ResourceType::getNextID()
{
	auto ret = mNextID;
	++mNextID;
	return ret;
}




