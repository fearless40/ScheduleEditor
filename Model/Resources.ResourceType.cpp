#include "pch.h"
#include <memory>
#include <algorithm>

#include "Model.h"
#include "Properties.PropertyTemplate.h"
#include "Resources.Resource.h"
#include "Resources.ResourceType.h"




namespace Model::Resources {

	

	// Kept for uniqueptr
	ResourceType::ResourceType() {};
	ResourceType::ResourceType(const Model::IndexConst index) : mIndex(index) {};
	ResourceType::ResourceType(const Model::IndexConst index, Properties::PropertyTemplate & pTemplate) : mIndex(index), mPropTemp(&pTemplate) { }
	ResourceType::~ResourceType() {};

	Resource & Model::Resources::ResourceType::create()
	{
		auto res = std::make_unique<Resource>(*this, getNextID());
		mItems.push_back(std::move(res));
		return *mItems.back();
	}

	Resource & Model::Resources::ResourceType::create(Model::Properties::PropertyMap && map)
	{
		auto res = std::make_unique<Resource>(*this, getNextID(), std::move(map));
		mItems.push_back(std::move(res));
		return *mItems.back();
	}

	Resource & ResourceType::load(ResourceID id, bool isDeleted, Model::Properties::PropertyMap && map)
	{
		auto res = std::make_unique<Resource>(*this, id, std::move(map));
		if (id >= mNextID) {
			mNextID = id + 1;
		}
		if (isDeleted) res->markAsDeleted();
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