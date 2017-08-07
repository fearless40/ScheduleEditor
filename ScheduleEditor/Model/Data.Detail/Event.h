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

	bool operator < (const EventHandle & h1, const EventHandle & h2) {
		return h1.value < h2.value;
	}

	bool operator > (const EventHandle & h1, const EventHandle & h2) {
		return h1.value > h2.value;
	}

	bool operator == (const EventHandle & h1, const EventHandle & h2) {
		return h1.value == h2.value;
	}

	bool operator != (const EventHandle & h1, const EventHandle & h2) {
		return h1.value != h2.value;
	}

	static constexpr EventHandle NullHandle{ 0 };

	struct Event {
		Model::Resources::Resource * value;
		Model::Properties::PropertyMap * properties;
		Model::Time::HourMinute start;
		Model::Time::Duration minutes;
		EventHandle handle;
	};

	bool operator < (const Event & e1, const EventHandle & h1) {
		return e1.handle < h1;
	}

	bool operator < (const Event & e1, const Event & e2) {
		return e1.handle < e2.handle;
	}

	bool operator < (const EventHandle & h1, const Event & e1 ) {
		return h1 < e1.handle;
	}

	bool operator == (const Event & e1, const EventHandle &h1) {
		return e1.handle == h1;
	}

	bool operator != (const Event & e1, const EventHandle &h1) {
		return e1.handle != h1;
	}
}