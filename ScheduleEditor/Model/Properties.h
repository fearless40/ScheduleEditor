#pragma once

#include <variant>

namespace Model::Properties {
	using Property = std::variant<long, double, bool, std::string>;
	using RangeProperty = std::variant<long, double>;

	enum class ValueTypes {
		vtLONG,
		vtBOOL,
		vtDOUBLE,
		vtSTRING
	};

	struct PropertyDefinition {
		std::string		name;
		bool			mandatory;
		ValueTypes		type;
		Property		defvalue;
		RangeProperty	min;
		RangeProperty	max;
	};
}