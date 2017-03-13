#pragma once

#include "Resources.h"

namespace Model::Resources {
	
	/// Holds a set of possible unrelated resources to allow easier user interaction and arbitray grouping
	// Owned by: self
	class ResourceGroup {
		/*Index mIndex;
		std::string mName;
		std::vector<const Resource *> mMembers;
		std::vector<uint32_t> mPriority;
		*/

	public:

		class iterator {};

		void insert(const Resource & resource, uint32_t priority);
		void remove(const Resource & resource);

		const iterator begin() const;
		const iterator end() const;

		bool contains(const Resource & resource);
		
		size_t count() const;
	};
}