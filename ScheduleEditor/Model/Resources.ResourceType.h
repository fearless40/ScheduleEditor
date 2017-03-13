#pragma once

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

		const iterator begin() const;
		const iterator end() const;

		iterator begin();
		iterator end();

		size_t count() const;

		const PropertTemplate & template_get() const;


	};
}