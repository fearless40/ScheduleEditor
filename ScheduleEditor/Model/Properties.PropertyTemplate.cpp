#include "pch.h"
#include <vector>
#include <algorithm>

#include "Model.h"
#include "Properties.h"
#include "Properties.PropertyTemplate.h"
#include "Properties.PropertyMap.h"
#include "../Utils/FixedList.h"

using namespace  Model::Properties;

Utility::FixedList<PropertyTemplate> templates;

void Model::Properties::PropertyTemplate::string_add(PropertyIndex name, std::string defaultvalue, bool mandatory)
{
	auto f = find(name);
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

void Model::Properties::PropertyTemplate::long_add(PropertyIndex name, long defaultvalue, long min, long max, bool mandatory)
{
	auto f = find(name);
	if ( f != mDefs.end())
	{
		(*f).defvalue = defaultvalue;
		(*f).mandatory = mandatory;
		(*f).min = min;
		(*f).max = max;
	}
	else {
		mDefs.emplace_back(name, mandatory, ValueTypes::vtLONG, defaultvalue, min, max);
	}
}

void Model::Properties::PropertyTemplate::double_add(PropertyIndex name, double defaultvalue, double min, double max, bool mandatory)
{
	auto f = find(name);
	if ( f != mDefs.end())
	{
		(*f).defvalue = defaultvalue;
		(*f).mandatory = mandatory;
		(*f).min = min;
		(*f).max = max;
	}
	else {
		mDefs.emplace_back(name, mandatory, ValueTypes::vtDOUBLE, defaultvalue, min, max);
	}
}

void Model::Properties::PropertyTemplate::bool_add(PropertyIndex name, bool defaultvalue, bool mandatory)
{
	auto f = find(name);
	if (f != mDefs.end())
	{
		(*f).defvalue = defaultvalue;
		(*f).mandatory = mandatory;
	}
	else {
		mDefs.emplace_back(name, mandatory, ValueTypes::vtBOOL, defaultvalue);
	}
}

bool Model::Properties::PropertyTemplate::validate(const PropertyMap & map) const
{
	return false;
}

void Model::Properties::PropertyTemplate::make_valid(PropertyMap & map) const
{
}

const PropertyTemplate & Model::Properties::PropertyTemplate::Find(Model::Index name)
{
	// TODO: insert return statement here
	auto it = templates.find(name);

	if (it == templates.end() )
	{
		throw "Could not find the item specified";
	}
	return *it;
}

PropertyTemplate Model::Properties::PropertyTemplate::Create(Model::Index name)
{
	// TODO: insert return statement here
	PropertyTemplate pt(name);
	if (templates.find(name) == templates.end()) {
		return pt;
	}
	else {
		throw "Item already exists in the collection.";
	}
}

void Model::Properties::PropertyTemplate::Save(PropertyTemplate & pt)
{
	auto item = templates.find(pt.index());
	if (item == templates.end()) {
		templates.insert(pt);
	}
	else {
		templates.modify(item, pt);
	}
}

PropertyTemplate Model::Properties::PropertyTemplate::Edit(const PropertyTemplate & pt)
{
	PropertyTemplate ret(pt);
	return ret;
}

std::vector<Model::Index> Model::Properties::PropertyTemplate::GetAllNames()
{
	std::vector<Model::Index> ret;
	std::for_each(templates.begin(), templates.end(), [&ret](auto & k) { ret.push_back(k.index()); });
	return ret;
}

Model::Properties::PropertyTemplate::PropertyDefinitions::iterator Model::Properties::PropertyTemplate::find(PropertyIndex index)
{
	return std::find_if(mDefs.begin(), mDefs.end(), [&index](auto const & item) { return item.name == index; });
}

Model::Properties::PropertyTemplate::PropertyTemplate(Model::Index index) : mIndex(index)
{
}
