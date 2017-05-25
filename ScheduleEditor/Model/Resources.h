#pragma once

namespace Model::Resources {
		
	class ResourceType;
	class Resource;
	class ResourceGroup;

	using ResourceID = uint16_t;

	struct ResourceUniqueID {
	//	ResourceID ResourceTypeID;
		ResourceID ResourceID;
	};


	// ResourceType owned by self. 
	// Resource owned by ResourceType
	// ResourceGroup owned by self. Points to Resource but does not own Resource

}