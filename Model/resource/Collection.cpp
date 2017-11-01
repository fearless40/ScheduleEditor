#include "pch.h"
#include <vector>
#include <algorithm>
#include "Collection.h"

namespace model::resource {

	void Collection::insert(const Value & resource)
	{
		auto finder = std::find(mMembers.begin(), mMembers.end(), &resource);
		if (finder != mMembers.end()) {
			mMembers.push_back(&resource);
		}
	}

	void Collection::remove(const Value & resource)
	{
		auto finder = std::find(mMembers.begin(), mMembers.end(), &resource);
		if (finder != mMembers.end()) {
			mMembers.erase(finder);
		}
	}

}