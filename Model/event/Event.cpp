#include "pch.h"
#include "../Model.h"
#include "Event.h"
#include "../resource/Value.h"
#include "../property/Map.h"

using namespace model::event;

model::property::Property Event::default_value() const
{
	if (value) {
		return value->value();
	} 
	else {
		if (properties) {
			auto found = properties->find("value");
			if (found == properties->end()) {
				return model::string();
			}
		}
	}
	return {0L};
}
