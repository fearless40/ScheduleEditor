pragma once

#include "Resources.h"

namespace Model::Resources {
	
	/// Owns a group of resources and defines the type of resource
	/// Owned by: self, obtain by using static functions
	class ResourceType
	{
		//Index mIndex;
		//std::string mName;
		//std::vector<Resource> mMembers;
		//const PropertyTemplate * mTemplate;

		// This items resource ID
		ResourceID mID;

		// The next resource that is created will use this value. Values are never recyeled. 
		ResourceID mNextResourceID;

	public:

		class iterator {};
		class const_iterator {};

		ResourceID getID() const; 

		const_iterator begin() const;
		const_iterator end() const;

		iterator begin();
		iterator end();

		size_t count() const;

		Resource & resource_create();
		void resource_remove(const_iterator it);

		const Model::Properties::PropertyTemplate & propertyTemplate() const;
		Model::Properties::PropertyTemplate & propertyTemplate();


		// Static functions
		static const ResourceType & Find(Model::Index name);
		static ResourceType & Create(Model::Index name);
		static void Save(ResourceType & rt);
		static ResourceType & Edit(const ResourceType & rt);
		static std::vector<Model::Index> GetAllNames();

		static const Resouce & FindResource(ResourceUniqueID id);
	};
}