#pragma once


#include "Resources.h"
#include "Model.h"
#include "ModelIndex.h"
#include "Properties.HasProperties.h"

namespace Model::Resources {
	
	/// Holds a set of possible unrelated resources to allow easier user interaction and arbitray grouping
	/// Owned by: ResourceGroupOwner
	class ResourceGroup : public Properties::HasProperties{
		Model::Index mIndex{ NullIndex };
		
		// Does not Own individual resources
		std::vector<const Resource *> mMembers;
		

	public:
		
		ResourceGroup() = default;
		ResourceGroup(Index index) : mIndex(index) {}
		ResourceGroup(const ResourceGroup & group) : mIndex(group.mIndex), mMembers(group.mMembers) { };
		ResourceGroup(ResourceGroup &&) = default;
		ResourceGroup & operator = (const ResourceGroup &) = default;

		Index index() const { return mIndex; }

		void insert(const Resource & resource);
		void remove(const Resource & resource);

		auto begin() const { return mMembers.begin(); }
		auto end() const { return mMembers.end(); }

		auto begin() { return mMembers.begin(); }
		auto end() { return mMembers.end();  }

		auto cbegin() const { return mMembers.cbegin(); }
		auto cend() const { return mMembers.cend(); }

		size_t size() const { return mMembers.size(); }

	};

	static ModelIndex<ResourceGroup> ResourceGroupOwner;
}