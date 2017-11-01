#pragma once

#include <chrono>
#undef min
#undef max
#include "../../Lib/date/date.h"

namespace model::time {

	using Duration = std::chrono::minutes;

	struct HourMinute {
		// Represents a duration from Midnight (00:00)
		// 24 hours: to represent 8:30 AM
		// hour = 8, minute = 30
		// to represent 5:33 PM
		// hour = 17, minute = 33

		unsigned char hour;
		unsigned char minute;

		operator model::time::Duration () {
			return std::chrono::hours(hour) + std::chrono::minutes(minute);
		}

		uint32_t minutes() const {
			return hour * 60 + minute;
		}
	};

	inline model::time::Duration operator + (model::time::HourMinute hm, model::time::Duration dur) {
		return static_cast<model::time::Duration>(hm) + dur;
	}

	inline model::time::Duration operator + (model::time::Duration dur, model::time::HourMinute hm) {
		return static_cast<model::time::Duration>(hm) + dur;
	}

	inline bool operator == (HourMinute lhs, HourMinute rhs) {
		return (lhs.hour == rhs.hour) && (lhs.minute == rhs.minute);
	}
	
	struct DateRange {
		date::year_month_day start;
		date::year_month_day end;
	};

	template <typename ChronoDuration>
	std::chrono::time_point<ChronoDuration> operator + (const HourMinute & hm, const std::chrono::time_point<ChronoDuration> tp) {
		return tp + std::chrono::hours(hm.hour) + std::chrono::minutes(hm.minute);
	}
}