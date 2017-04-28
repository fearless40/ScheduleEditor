#pragma once

#include <variant>

namespace Model::Properties {
	using Property = std::variant<long, double, bool, std::string>;
	using RangeProperty = std::variant<long, double>;
	using PropertyIndex = std::string;

	enum class ValueTypes {
		vtLONG,
		vtBOOL,
		vtDOUBLE,
		vtSTRING
	};

	struct PropertyDefinition {
		PropertyIndex	name;
		bool			mandatory;
		ValueTypes		type;
		Property		defvalue;
		RangeProperty	min;
		RangeProperty	max;
		const PropertyIndex & index() { return name;  }
	};

	class PropertyMap; 
	class ProperyTemplate;

	// PropertyMap are owned by the class that contains it. 

	// PropertyTemplates are global ownership and must be retrieved by name
}