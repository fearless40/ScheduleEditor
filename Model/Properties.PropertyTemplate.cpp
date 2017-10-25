#include "pch.h"
#include <vector>
#include <algorithm>

#include "Model.h"
#include "ModelIndex.h"
#include "Properties.PropertyTemplate.h"
#include "Properties.PropertyMap.h"

using namespace  Model;
using namespace  Model::Properties;

ModelIndex<PropertyTemplate> PropertyTemplateOwner;


PropertyTemplate::PropertyTemplate() : mIndex(NullIndex)
{

}

void PropertyTemplate::string_add(Key name, Model::string defaultvalue, bool mandatory)
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

void Model::Properties::PropertyTemplate::long_add(Key name, long defaultvalue, long min, long max, bool mandatory)
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

void Model::Properties::PropertyTemplate::double_add(Key name, double defaultvalue, double min, double max, bool mandatory)
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

void Model::Properties::PropertyTemplate::bool_add(Key name, bool defaultvalue, bool mandatory)
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

Model::Properties::PropertyTemplate::PropertyDefinitions::iterator Model::Properties::PropertyTemplate::find(Key index)
{
	return std::find_if(mDefs.begin(), mDefs.end(), [&index](auto const & item) { return item.name == index; });
}

/*
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
		templates.replace(item, pt);
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

*/

