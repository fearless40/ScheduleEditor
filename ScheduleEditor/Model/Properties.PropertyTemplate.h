#pragma once

#include <vector>
#include "Properties.h"

namespace Model::Properties {
	
	class PropertyTemplate {
	public:
		using PropertyDefinitions = std::vector<PropertyDefinition>;

		void string_add(PropertyIndex name, std::string defaultvalue, bool mandatory = false);
		void long_add(PropertyIndex name, long defaultvalue, long min, long max, bool mandatory = false);
		void double_add(PropertyIndex name, double defaultvalue, double min, double max, bool mandatory = false);
		void bool_add(PropertyIndex name, bool defaultvalue, bool mandatory = false);

		/// Validates a propertymap and returns true if the propertymap matches the definition in the template
		bool validate(const PropertyMap & map) const;

		/// Makes the PropertyMap valid by adding memebers and changing values if out of range
		void make_valid(PropertyMap & map) const;

		// Static functions

		static const PropertyTemplate & Find(Model::Index name);
		static PropertyTemplate & Create(Model::Index name);
		static void Save(PropertyTemplate & pt);
		static PropertyTemplate & Edit(const PropertyTemplate & pt);
		std::vector<Model::Index> GetAllNames()


	private:

		PropertyDefinitions mDefs;

		// Used to look it up 
		//Index mIndex;
	};
}
