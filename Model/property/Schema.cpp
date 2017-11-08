#include "pch.h"
#include <vector>
#include <algorithm>

#include "model.h"
#include "Map.h"
#include "Schema.h"



using namespace  model::property;


Schema::Schema() : mIndex(NullIndex)
{

}

void Schema::string_add(Key name, model::string defaultvalue, bool mandatory)
{
	auto f = this->find(name);
	if (f != mDefs.end())
	{
		// Overwrite the existing definition
		(*f).defvalue = defaultvalue;
		(*f).mandatory = mandatory;
	}
	else {
		mDefs.emplace_back(name, mandatory, ValueTypes::vtSTRING, defaultvalue);
	}
}

void Schema::long_add(Key name, long defaultvalue, long min, long max, bool mandatory)
{
	auto f = this->find(name);
	if ( f != mDefs.end())
	{
		(*f).defvalue = defaultvalue;
		(*f).mandatory = mandatory;
		(*f).minvalue = min;
		(*f).maxvalue = max;
	}
	else {
		mDefs.emplace_back(name, mandatory, ValueTypes::vtLONG, defaultvalue, min, max);
	}
}

void Schema::double_add(Key name, double defaultvalue, double min, double max, bool mandatory)
{
	auto f = find(name);
	if ( f != mDefs.end())
	{
		(*f).defvalue = defaultvalue;
		(*f).mandatory = mandatory;
		(*f).minvalue = min;
		(*f).maxvalue = max;
	}
	else {
		mDefs.emplace_back(name, mandatory, ValueTypes::vtDOUBLE, defaultvalue, min, max);
	}
}

void Schema::bool_add(Key name, bool defaultvalue, bool mandatory)
{
	auto f = find(name);
	if (f != mDefs.end())
	{
		(*f).defvalue = static_cast<long>(defaultvalue);
		(*f).mandatory = mandatory;
	}
	else {
		mDefs.emplace_back(name, mandatory, ValueTypes::vtBOOL, static_cast<long>(defaultvalue));
	}
}

bool Schema::validate(const Map & map) const
{
	return false;
}

void Schema::make_valid(Map & map) const
{
}

Schema::PropertyDefinitions::iterator Schema::find(Key index)
{
	return std::find_if(mDefs.begin(), mDefs.end(), [&index](auto const & item) { return item.name == index; });
}



