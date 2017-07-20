#pragma once

#include <vector>
//#include "ModelIndex.h"
#include "Properties.h"

namespace Model::Properties {
	
	

	class PropertyTemplate {
	public:
		using PropertyDefinitions = std::vector<PropertyDefinition>;

		PropertyTemplate();
		PropertyTemplate(const PropertyTemplate & pt) = default;
		PropertyTemplate(PropertyTemplate && pt) = default;
		PropertyTemplate(Index index) : mIndex(index) {}
		PropertyTemplate & operator = (const PropertyTemplate & pt) = default;

		Model::Index index() const { return mIndex; }

		auto cbegin() const { return mIndex.cbegin(); }
		auto cend() const { return mIndex.cend(); }

		auto begin() { return mIndex.begin(); }
		auto end() { return mIndex.end(); }

		void string_add(PropertyIndex name, std::string defaultvalue, bool mandatory = false);
		void long_add(PropertyIndex name, long defaultvalue, long min, long max, bool mandatory = false);
		void double_add(PropertyIndex name, double defaultvalue, double min, double max, bool mandatory = false);
		void bool_add(PropertyIndex name, bool defaultvalue, bool mandatory = false);
		
		void remove(PropertyIndex name);

		/// Validates a propertymap and returns true if the propertymap matches the definition in the template
		bool validate(const PropertyMap & map) const;

		/// Makes the PropertyMap valid by adding memebers and changing values if out of range
		void make_valid(PropertyMap & map) const;

	

	private:

		PropertyDefinitions::iterator find(PropertyIndex index);

		PropertyDefinitions mDefs;

		// Used to look it up 
		Model::Index mIndex;

			
	};

	static ModelIndex<PropertyTemplate> PropertyTemplateOwner;

}
