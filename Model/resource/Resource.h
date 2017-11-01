#pragma once

namespace model::resource {
		
	class Type;
	class Value;
	class ResourceGroup;

	using ResourceID = uint32_t;

	

	// ResourceType owned by static ResourceTypeOwner. 
	// Resource owned by ResourceType
	// ResourceGroup owned by static ResourceGroupOwner. Points to Resource but does not own Resource

}