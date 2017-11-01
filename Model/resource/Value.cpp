#include "pch.h"
#include <sstream>
#include <variant>
#include "Value.h"

using namespace model::resource;

Value::Value(const Type & owner, ResourceID id) :
	mType{ owner },
	mId{id},
	Map(default_key, default_value_value )
{
}

Value::Value(const Type & owner, ResourceID id, model::property::Map && pmap) :
	mType{ owner },
	mId{ id },
	Map{std::move(pmap)}
{
}
