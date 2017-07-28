#pragma once

#include "../TimeDuration.h"

class Model::Resources::Resource;
class Model::Properties::PropertyMap;

namespace Model::Data::Detail {
	
	

	union EventHandle {
		struct FIELDS{
			uint32_t year : 12;
			uint32_t month : 4;
			uint32_t day : 5;
			uint32_t minute : 11;
		};
		FIELDS fields;
		uint32_t value;
	};

	static constexpr EventHandle NullHandle{ 0 };

	struct Event {
		Model::Resources::Resource * value;
		Model::Properties::PropertyMap * properties;
		Model::Time::HourMinute start;
		Model::Time::Duration minutes;
		EventHandle handle;
	};
}