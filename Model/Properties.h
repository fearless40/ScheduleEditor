#pragma once

#include <variant>
#include "Model.h"

namespace Model::Properties {
	using Property = std::variant<long, double, bool, std::wstring>;
	using RangeProperty = std::variant<long, double>;
	using Key = std::string;
	using KeyConst = std::string_view;

	Model::string PropertyAsString(const Property & prop);

	enum class ValueTypes {
		vtLONG,
		vtBOOL,
		vtDOUBLE,
		vtSTRING
	};


	struct PropertyDefinition {
		Key				name;
		bool			mandatory;
		ValueTypes		type;
		Property		defvalue;
		RangeProperty	minvalue;
		RangeProperty	maxvalue;
		const Key & index() { return name;  }

		PropertyDefinition(Key tname, bool tMandatory, ValueTypes ttype, Property tdefvalue, RangeProperty tmin, RangeProperty tmax) :
			name(tname), mandatory(tMandatory), type(ttype), defvalue(tdefvalue), minvalue(tmin), maxvalue(tmax) {};
		PropertyDefinition(Key tname, bool tMandatory, ValueTypes ttype, Property tdefvalue) :
			name(tname), mandatory(tMandatory), type(ttype), defvalue(tdefvalue) {};
		PropertyDefinition(PropertyDefinition && pd) = default;
		PropertyDefinition(const PropertyDefinition & pd) = default;
		PropertyDefinition & operator = (const PropertyDefinition & pd) = default;
	};

	inline bool operator == (const PropertyDefinition & pd, const Key & pi) {
		return pd.name == pi;
	}

	inline bool operator == (const Key & pi, const PropertyDefinition & pd) {
		return pd.name == pi;
	}

	class PropertyMap; 
	class ProperyTemplate;

	// PropertyMap are owned by the class that contains it. 

	// PropertyTemplates are global ownership and must be retrieved by name
}