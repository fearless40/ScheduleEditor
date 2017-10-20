#include "pch.h"
#include <vector>
#include <algorithm>
#include "Properties.PropertyMap.h"
#include "Resources.ResourceGroup.h"

namespace Model::Resources {

	//ModelIndex<ResourceGroup> ResourceGroupOwner;

	void ResourceGroup::insert(const Resource & resource)
	{
		auto finder = std::find(mMembers.begin(), mMembers.end(), &resource);
		if (finder != mMembers.end()) {
			mMembers.push_back(&resource);
		}
	}

	void ResourceGroup::remove(const Resource & resource)
	{
		auto finder = std::find(mMembers.begin(), mMembers.end(), &resource);
		if (finder != mMembers.end()) {
			mMembers.erase(finder);
		}
	}

}