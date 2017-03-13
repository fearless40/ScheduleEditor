#pragma once

namespace Model {
	namespace Resources {
		
		ResourceGroup & Get_Name(std::string name);
		ResourceGroup & Get_Index(Index mIndex);

		ResourceGroup & Create(Index mIndex, std::string name);

		void			Remove(ResourceGroup * rg);

		// Groups a set of resources together. Order is enforced by position within the vector
		class ResourceGroup {
			Index mIndex;
			std::string mName;
			std::vector<const Resource *> mMembers;
			std::vector<uint32_t> mPriority;
			

		public:
			//find()
			//begin()
			//end()
			//add()
			//remove()
			//count();
		};
		
		// Owns a resource. Every resource must have a defining type
		class ResourceType
		{
			Index mIndex;
			std::string mName;
			std::vector<Resource> mMembers;
			const PropertyTemplate * mTemplate;
		};

		
		class Resource
		{
			Properties::PropertyMap mProperties;
			const ResourceType & mType;

		public:
			static Resource NullResource;

			const Model::Properties::PropertyMap & properties_get();

			// Helpful to allow if() like constructs to check if something is empty or null
			operator bool() { return (this != &NullResource); }


		};
	}
}