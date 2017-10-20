#pragma once

#include "Model.h"
#include "Resources.h"


namespace Model::Resources {

	class ResourceType;
	class Resource;

	template <class T>
	class ResourceHandle;

	template <>
	class ResourceHandle<Model::Index> {
		operator Resource() {

		}

	};

	template <>
	class ResourceHandle <ResourceType *>
	{
		ResourceType * owner;
		ResourceID		item;

	public:
		ResourceHandle() = default;
		ResourceHandle(ResourceType *tp, ResourceID id) : owner(tp), item(id) {}
		ResourceHandle(const ResourceHandle & rh) = default;
		ResourceHandle(ResourceHandle && rh) = default;
		ResourceHandle & operator = (const ResourceHandle & r) = default;

		// Smart pointer like functions
		const ResourceType * owner() const { return owner; }
		const Resource & get() const { return owner->lookup(ResourceID); }
		Resource & get() { return owner->lookup(ResourceID); }

		
		// Emulate a Resource item
		Model::Properties::PropertyMap & properties() {
			return get().properties();
		}

		const Model::Properties::PropertyMap & properties() const {
			return get().properties();
		}

		ResourceUniqueID getID() const { return get().getID(); }

		// Conversion funtion
		operator Resource() {
			return get();
		}

	};

};