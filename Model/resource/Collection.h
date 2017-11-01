#pragma once


#include "Resource.h"
#include "model.h"
#include "property\InheritPropertyMap.h"

namespace model::resource {
	
	/// Holds a set of possible unrelated resources to allow easier user interaction and arbitray grouping
	/// Owned by: ResourceGroupOwner
	class Collection : public model::property::InheritPropertyMap{
		model::Index mIndex{ NullIndex };
		
		// Does not Own individual resources
		std::vector<const model::resource::Value *> mMembers;
		

	public:
		
		Collection() = default;
		Collection(Index index) : mIndex(index) {}
		Collection(const Collection & group) : mIndex(group.mIndex), mMembers(group.mMembers) { };
		Collection(Collection &&) = default;
		Collection & operator = (const Collection &) = default;

		Index index() const { return mIndex; }

		void insert(const model::resource::Value & resource);
		void remove(const model::resource::Value & resource);

		auto begin() const { return mMembers.begin(); }
		auto end() const { return mMembers.end(); }

		auto begin() { return mMembers.begin(); }
		auto end() { return mMembers.end();  }

		auto cbegin() const { return mMembers.cbegin(); }
		auto cend() const { return mMembers.cend(); }

		size_t size() const { return mMembers.size(); }

	};

	
}