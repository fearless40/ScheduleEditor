#pragma once
#include "Model.h"
#include "ModelIndex.h"
#include "Resources.Resource.h"
#include "Properties.PropertyTemplate.h"

namespace Model::Resources  {
	
	/// Owns a group of resources and defines the type of resource
	/// Owned by: self, obtain by using static functions
	class ResourceType : public ModelIndex<ResourceType>
	{
		//Index mIndex;
		//std::string mName;
		//std::vector<Resource> mMembers;
		//const PropertyTemplate * mTemplate;

	public:

		Model::Index index() const { return mIndex;  }


		auto cbegin() const { return mItems.cbegin(); }
		auto cend() const { return mItems.cend();  }

		auto begin() { return mItems.begin(); }
		auto end() { return mItems.end(); }

		auto begin() const { return cbegin(); }
		auto end() const { return cend(); }

		size_t count() const;

		const Model::Properties::PropertyTemplate & propertyTemplate() const { return mPropTemp; }
		Model::Properties::PropertyTemplate & propertyTemplate() { return mPropTemp;  }


		// Static functions Inherited from the template
		/*static const ResourceType & Find(Model::Index name);
		static ResourceType & Create(Model::Index name);
		static void Save(ResourceType & rt);
		static ResourceType & Edit(const ResourceType & rt);
		std::vector<Model::Index> GetAllNames();*/
	private:
		Model::Index mIndex;
		Utility::FixedList<Resource> mItems;
		Model::Properties::PropertyTemplate mPropTemp;
	};
}