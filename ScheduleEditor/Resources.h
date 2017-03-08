#pragma once

namespace Model {
	namespace Resources {
		
		class Group {
			Index mIndex;
			std::string mName;
			std::vector<Resource> mMembers;
		};
		
		class Resource
		{
		public:
			const Properties::PropertyMap & properties_get();


		protected:
			Index mIndex;

			
			Properties::PropertyMap mProperties;

		};
	}
}