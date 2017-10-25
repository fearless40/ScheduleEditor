#pragma once
#include "boost\iterator\indirect_iterator.hpp"

#include "Model.h"
#include "ModelIndex.h"
//#include "Resources.Resource.h"
#include "Properties.PropertyTemplate.h"
#include "Properties.HasProperties.h"


namespace Model::Resources  {
	
	/// Owns a group of resources and defines the type of resource
	/// Owned by: self, obtain by using static functions
	class ResourceType : public Properties::HasProperties
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
		Resource & create(Model::Properties::PropertyMap && map);
		Resource & load(ResourceID id, bool isDeleted, Model::Properties::PropertyMap && map);
		void remove(const Resource & r);
		
		
		const Model::Properties::PropertyTemplate * propertyTemplate() const;


		/// Set a new PropertyTemplate to the class.
		void propertyTemplate_set(const Properties::PropertyTemplate & propt) {
			mPropTemp = &propt;
		}
		

		//const auto & properties() const { return mProperties; }
		//auto & properties() { return mProperties; }

		ResourceType();
		~ResourceType();
		ResourceType(const Model::Index & index);
		ResourceType(const Model::Index & index, Properties::PropertyTemplate & pTemplate); 
		ResourceType(ResourceType &&) = default;
		ResourceType & operator = (ResourceType &&) = default;

	private:
		Model::Index mIndex{ Model::NullIndex };
		
		// Todo: determine if having a vector here is better or a list. A list allows direct memory access without having to worry about a resource being moved.
		// The vector is much faster iteration at the cost of greater difficluty coding as it is safe for reading at the same time but not editing. It would therefore
		// require mutexs and such to get it to work.
		std::vector<std::unique_ptr<Resource>> mItems;

		/// Optional holds a pointer to a PropertyTemplate. Allows one to apply a template to each of the sub resource
		/// included in the group
		const Properties::PropertyTemplate * mPropTemp{ nullptr };
		//Model::Properties::PropertyMap mProperties;

		ResourceID mNextID{ 1 };

		ResourceID getNextID();
	};

	//static ModelIndex<ResourceType> ResourceTypeOwner;
	using ResourceTypeOwner = ModelIndex<ResourceType>;
}