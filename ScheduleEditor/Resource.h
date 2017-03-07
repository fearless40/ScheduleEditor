#pragma once

namespace Model {
	namespace Resources {
		
		class ResourceCategory {
			Index mIndex;
			std::string name;
			Properties::PropertyMap mProperties;
		};
		
		class Resource
		{
		public:
			const Properties::PropertyMap & properties_get();


		protected:
			Index mIndex;
			const ResourceCategory * mCategory;
			
			Properties::PropertyMap mProperties;

		};
	}
}