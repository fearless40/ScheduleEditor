#pragma once

namespace Model::Resources {
		
	class ResourceType;
	class Resource;
	class ResourceGroup;

	//using ResourceID = uint32_t;

	

	// ResourceType owned by static ResourceTypeOwner. 
	// Resource owned by ResourceType
	// ResourceGroup owned by static ResourceGroupOwner. Points to Resource but does not own Resource

}