#include "pch.h"
#include <vector>
#include "Model.h"
#include "Properties.h"
#include "Properties.PropertyTemplate.h"

using namespace  Model::Properties;


void Model::Properties::PropertyTemplate::string_add(PropertyIndex name, std::string defaultvalue, bool mandatory)
{
	mDefs.emplace_back(name, mandatory, ValueTypes::vtSTRING, defaultvalue);
}
