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
		class const_iterator {};

		void insert(const Resource & resource, uint32_t priority);
		void remove(const Resource & resource);

		const_iterator begin() const;
		const_iterator end() const;

		iterator begin();
		iterator end();

		bool contains(const Resource & resource);
		
		size_t count() const;

		// Static functions
		static const ResourceGroup & Find(Model::Index name);
		static ResourceGroup & Create(Model::Index name);
		static void Save(ResourceGroup & rt);
		static ResourceGroup & Edit(const ResourceGroup & rt);
		std::vector<Model::Index> GetAllNames();
	};
}