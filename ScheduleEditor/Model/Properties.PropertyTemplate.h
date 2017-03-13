#pragma once

#include "Properties.h"

namespace Model::Properties {
	
	class PropertyTemplate {
	public:
		using PropertyDefinitions = std::vector<PropertyDefinition>;

		void string_add(std::string name, std::string defaultvalue, bool mandatory = false);
		void long_add(std::string name, long defaultvalue, long min, long max, bool mandatory = false);
		void double_add(std::string name, double defaultvalue, double min, double max, bool mandatory = false);
		void bool_add(std::string name, bool defaultvalue, bool mandatory = false);



	private:

		PropertyDefinitions mDefinitions;

		// Used to look it up 
		//Index mIndex;
	};
}
