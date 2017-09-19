#pragma once

#include "../TimeDuration.h"

class Model::Resources::Resource;
class Model::Properties::PropertyMap;

namespace Model::Data::Detail {
	

	union EventHandle {
		struct FIELDS{
			uint32_t year : 12;
			uint32_t  month : 4;
			uint32_t  day : 5;
			uint32_t  minute : 11;
		};
		FIELDS fields;
		uint32_t  value;

		operator date::year_month_day() const {
			return date::year_month_day(date::year(fields.year), date::month(fields.month), date::day(fields.day));
		}
	};

	constexpr EventHandle NullHandle{ 0 };
	

	EventHandle make_handle(date::year_month_day day, Time::HourMinute start) {
		EventHandle hand;
		hand.fields.year = (uint32_t)(int)day.year();
		hand.fields.month = (uint32_t)day.month();
		hand.fields.day = (uint32_t)day.day();
		hand.fields.minute = start.minutes();
		return hand;
	}

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
		EventHandle handle;
		Model::Time::HourMinute start;
		Model::Time::Duration minutes;
		Model::Resources::Resource * value; // non owner
		Model::Properties::PropertyMapUniquePtr properties; //owner

		operator Model::Data::Event () const {
			return Model::Data::Event(handle, start, minutes, value, properties.get());
		}
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

	bool operator == (const EventHandle &h1, const Event & e1) {
		return e1.handle == h1;
	}

	bool operator != (const Event & e1, const EventHandle &h1) {
		return e1.handle != h1;
	}

	bool operator < (const Event & e1, const date::year_month_day & h1) {
		return e1.handle < h1;
	}

	bool operator < (const date::year_month_day & h1, const Event & e1 ) {
		return  h1 < e1.handle;
	}

	bool operator == (const Event & e1, const date::year_month_day & h1) {
		return e1.handle == h1;
	}

}

namespace std {
	template<> struct hash<Model::Data::Detail::EventHandle>
	{
		typedef Model::Data::Detail::EventHandle argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& s) const
		{
			return std::hash<uint32_t>{}(s.value);
		}
	};
}