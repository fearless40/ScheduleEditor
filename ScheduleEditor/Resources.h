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
		};
		
		class Resource
		{
		public:
			const Model::Properties::PropertyMap & properties_get();


		protected:
			Index mIndex;
			const ResourceGroup * const mOwner;

			
			Properties::PropertyMap mProperties;

		};
	}
}