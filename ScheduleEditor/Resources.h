#pragma once

namespace Model {
	namespace Resources {
		
		ResourceGroup & Get_Name(std::string name);
		ResourceGroup & Get_Index(Index mIndex);

		ResourceGroup & Create(Index mIndex, std::string name);

		void			Remove(ResourceGroup * rg);

		class ResourceGroup {
			Index mIndex;
			std::string mName;
			std::vector<Resource> mMembers;
			const PropertyTemplate * mTemplate;

		public:
			//find()
			//begin()
			//end()
			//add()
			//remove()
			//count();
		};
		
		class Resource
		{
		public:
			static Resource NullResource;

			const Model::Properties::PropertyMap & properties_get();

			// Helpful to allow if() like constructs to check if something is empty or null
			operator bool() { return (this != &NullResource); }

		protected:
			//Index mIndex;
			const ResourceGroup * const mOwner;

			
			Properties::PropertyMap mProperties;

		};
	}
}