#pragma once


#include "Resources.h"
#include "Model.h"
#include "ModelIndex.h"

namespace Model::Resources {
	
	/// Holds a set of possible unrelated resources to allow easier user interaction and arbitray grouping
	// Owned by: self
	class ResourceGroup : public ModelIndex<ResourceGroup> {
		Model::Index mIndex;
		Model::Properties::PropertyMap mPropMap;
		std::vector<std::reference_wrapper<Resource>> mMembers;
		

	public:

		//todo: Order may be important in this class. There may need to be a way to set which resources are first or sort them in some way
		
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
}