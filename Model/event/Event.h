#pragma once

#include "../TimeDuration.h"
#include <memory>
#include "../resource/Resource.h"
#include "../property/Property.h"

class model::resource::Value;
//class model::property::Map;

namespace model::event {
	

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
	

	inline EventHandle make_handle(date::year_month_day day, model::time::HourMinute start) {
		EventHandle hand;
		hand.fields.year = (uint32_t)(int)day.year();
		hand.fields.month = (uint32_t)day.month();
		hand.fields.day = (uint32_t)day.day();
		hand.fields.minute = start.minutes();
		return hand;
	}

	inline bool operator < (const EventHandle & h1, const EventHandle & h2) {
		return h1.value < h2.value;
	}

	inline bool operator > (const EventHandle & h1, const EventHandle & h2) {
		return h1.value > h2.value;
	}

	inline bool operator == (const EventHandle & h1, const EventHandle & h2) {
		return h1.value == h2.value;
	}

	inline bool operator != (const EventHandle & h1, const EventHandle & h2) {
		return h1.value != h2.value;
	}

	struct Event {
		EventHandle handle{ 0 };
		model::time::HourMinute start;
		model::time::Duration minutes;
		const model::resource::Value * value{ nullptr };
		std::shared_ptr<const model::property::Map> properties{ nullptr };

		date::year_month_day date() const noexcept { return handle; }

		model::property::Property default_value() const;
	};

	

	inline bool operator < (const Event & e1, const EventHandle & h1) {
		return e1.handle < h1;
	}

	inline bool operator < (const Event & e1, const Event & e2) {
		return e1.handle < e2.handle;
	}

	inline bool operator < (const EventHandle & h1, const Event & e1 ) {
		return h1 < e1.handle;
	}

	inline bool operator == (const Event & e1, const EventHandle &h1) {
		return e1.handle == h1;
	}

	inline bool operator == (const EventHandle &h1, const Event & e1) {
		return e1.handle == h1;
	}

	inline bool operator != (const Event & e1, const EventHandle &h1) {
		return e1.handle != h1;
	}

	inline bool operator < (const Event & e1, const date::year_month_day & h1) {
		return e1.handle < h1;
	}

	inline bool operator < (const date::year_month_day & h1, const Event & e1 ) {
		return  h1 < e1.handle;
	}

	inline bool operator == (const Event & e1, const date::year_month_day & h1) {
		return e1.handle == h1;
	}

}

namespace std {
	template<> struct hash<model::event::EventHandle>
	{
		typedef model::event::EventHandle argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& s) const
		{
			return std::hash<uint32_t>{}(s.value);
		}
	};
}