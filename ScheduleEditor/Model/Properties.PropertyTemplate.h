#pragma once

#include <vector>
#include "Properties.h"

namespace Model::Properties {
	
	class PropertyTemplate {
	public:
		using PropertyDefinitions = std::vector<PropertyDefinition>;

		void string_add(std::string name, std::string defaultvalue, bool mandatory = false);
		void long_add(std::string name, long defaultvalue, long min, long max, bool mandatory = false);
		void double_add(std::string name, double defaultvalue, double min, double max, bool mandatory = false);
		void bool_add(std::string name, bool defaultvalue, bool mandatory = false);

		/// Validates a propertymap and returns true if the propertymap matches the definition in the template
		bool validate(const PropertyMap & map) const;

		/// Makes the PropertyMap valid by adding memebers and changing values if out of range
		void make_valid(PropertyMap & map) const;

		// Static functions

		static const PropertyTemplate & Find(std::string name);
		static PropertyTemplate & Create(std::string name);
		static void Save(PropertyTemplate & pt);
		static PropertyTemplate & Edit(const PropertyTemplate & pt);
		std::vector<Model::Index> GetAllNames()


	private:

		PropertyDefinitions mDefinitions;

		// Used to look it up 
		//Index mIndex;
	};
}
