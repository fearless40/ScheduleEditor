#pragma once

#include <variant>
#include "model.h"

namespace model::property {
	using Property = std::variant<long, double, std::wstring>;
	using RangeProperty = std::variant<long, double>;
	using Key = std::string;
	using KeyConst = std::string_view;


	model::string PropertyAsString(const Property & prop);

	enum class ValueTypes {
		vtLONG,
		vtBOOL,
		vtDOUBLE,
		vtSTRING
	};


	struct Definition {
		Key				name;
		bool			mandatory;
		ValueTypes		type;
		Property		defvalue;
		RangeProperty	minvalue;
		RangeProperty	maxvalue;
		const Key & index() { return name;  }

		Definition(Key tname, bool tMandatory, ValueTypes ttype, Property tdefvalue, RangeProperty tmin, RangeProperty tmax) :
			name(tname), mandatory(tMandatory), type(ttype), defvalue(tdefvalue), minvalue(tmin), maxvalue(tmax) {};
		Definition(Key tname, bool tMandatory, ValueTypes ttype, Property tdefvalue) :
			name(tname), mandatory(tMandatory), type(ttype), defvalue(tdefvalue) {};
		Definition(Definition && pd) = default;
		Definition(const Definition & pd) = default;
		Definition & operator = (const Definition & pd) = default;
	};

	inline bool operator == (const Definition & pd, const Key & pi) {
		return pd.name == pi;
	}

	inline bool operator == (const Key & pi, const Definition & pd) {
		return pd.name == pi;
	}

	class Collection; 
	class Template;

	// PropertyMap are owned by the class that contains it. 

	// PropertyTemplates are global ownership and must be retrieved by name
}