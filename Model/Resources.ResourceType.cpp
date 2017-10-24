#include "pch.h"
#include <memory>
#include <algorithm>

#include "Model.h"
#include "ModelIndex.h"
#include "Properties.PropertyTemplate.h"
#include "Resources.Resource.h"
#include "Resources.ResourceType.h"




namespace Model::Resources {

	

	// Kept for uniqueptr
	ResourceType::ResourceType() {};
	ResourceType::ResourceType(const Model::Index & index) : mIndex(index) {};
	ResourceType::ResourceType(const Model::Index & index, Properties::PropertyTemplate & pTemplate) : mIndex(index), mPropTemp(&pTemplate) { }
	ResourceType::~ResourceType() {};

	Resource & Model::Resources::ResourceType::create()
	{
		auto res = std::make_unique<Resource>(*this, getNextID());
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
		if (&(r.resource_type()) != this) {
			return;
		}

		auto res = std::find_if(mItems.begin(), mItems.end(), [&](const auto & v) {
			if (v->id() == r.id()) {
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

	const Model::Properties::PropertyTemplate * Model::Resources::ResourceType::propertyTemplate() const
	{
		return mPropTemp;
	}


	ResourceID Model::Resources::ResourceType::getNextID()
	{
		auto ret = mNextID;
		++mNextID;
		return ret;
	}




}