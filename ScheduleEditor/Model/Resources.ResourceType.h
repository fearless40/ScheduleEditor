#pragma once
//#include "Model.h"

namespace Model::Resources {
	
	/// Owns a group of resources and defines the type of resource
	/// Owned by: self, obtain by using static functions
	class ResourceType
	{
		//Index mIndex;
		//std::string mName;
		//std::vector<Resource> mMembers;
		//const PropertyTemplate * mTemplate;

	public:

		class iterator {};
		class const_iterator {};

		const_iterator begin() const;
		const_iterator end() const;

		iterator begin();
		iterator end();

		size_t count() const;

		const Model::Properties::PropertyTemplate & propertyTemplate() const;
		Model::Properties::PropertyTemplate & propertyTemplate();


		// Static functions
		static const ResourceType & Find(Model::Index name);
		static ResourceType & Create(Model::Index name);
		static void Save(ResourceType & rt);
		static ResourceType & Edit(const ResourceType & rt);
		std::vector<Model::Index> GetAllNames();
	};
}