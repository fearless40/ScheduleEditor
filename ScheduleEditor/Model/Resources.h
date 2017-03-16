#pragma once

namespace Model::Resources {
		
	class ResourceType;
	class Resource;
	class ResourceGroup;

	// ResourceType owned by self. 
	// Resource owned by ResourceType
	// ResourceGroup owned by self. Points to Resource but does not own Resource

}