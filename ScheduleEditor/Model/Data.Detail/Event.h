#pragma once

namespace Model::Data::Detail {
	
	class Model::Resources::Resource;
	class Model::Properties::PropertyMap;

	union EventHandle {
		struct {
			uint32_t year : 12;
			uint32_t month : 4;
			uint32_t day : 5;
			uint32_t minute : 11;
		} fields;
		uint32_t value;
	};

	static constexpr EventHandle NullHandle{ 0 };

	struct Event {
		Model::Resources::Resource * value;
		Model::Properties::PropertyMap * properties;
		Time::HourMinute start;
		Time::Duration minutes;
		EventHandle handle;
	};
}