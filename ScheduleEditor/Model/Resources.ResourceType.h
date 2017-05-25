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

		const auto & properties() const { return mProperties; }
		auto & properties() { return mProperties; }

		// Static functions Inherited from the template
		/*static const ResourceType & Find(Model::Index name);
		static ResourceType & Create(Model::Index name);
		static void Save(ResourceType & rt);
		static ResourceType & Edit(const ResourceType & rt);
		std::vector<Model::Index> GetAllNames();*/
	private:
		Model::Index mIndex;
		
		// Todo: determine if having a vector here is better or a list. A list allows direct memory access without having to worry about a resource being moved.
		// The vector is much faster iteration at the cost of greater difficluty coding as it is safe for reading at the same time but not editing. It would therefore
		// require mutexs and such to get it to work.
		Utility::FixedList<Resource> mItems;
		
		Model::Properties::PropertyTemplate mPropTemp;
		Model::Properties::PropertyMap mProperties;
	};
}