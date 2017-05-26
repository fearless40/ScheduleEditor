#pragma once
#include <boost\iterator\indirect_iterator.hpp>

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
		using IndirectAdaptor = boost::indirect_iterator<std::vector<std::unique_ptr<Resource>>::iterator, Resource &>;
		using ConstIndirectAdaptor = boost::indirect_iterator<std::vector<std::unique_ptr<Resource>>::const_iterator, const Resource &>;

		Model::Index index() const { return mIndex;  }


		auto cbegin() const { return ConstIndirectAdaptor(mItems.cbegin()); }
		auto cend() const { return ConstIndirectAdaptor(mItems.cend());  }

		auto begin() { return IndirectAdaptor(mItems.begin()); }
		auto end() { return IndirectAdaptor(mItems.end()); }

		auto begin() const { return cbegin(); }
		auto end() const { return cend(); }

		size_t size() const { return mItems.size(); }

		Resource & create();
		Resource & create(const Model::Properties::PropertyMap & map);
		void remove(const Resource & r);
		
		
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
		std::vector<std::unique_ptr<Resource>> mItems;

		
		Model::Properties::PropertyTemplate mPropTemp;
		Model::Properties::PropertyMap mProperties;
	};
}