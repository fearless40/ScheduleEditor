#pragma once

#include <chrono>

namespace Model::Time {

	using Duration = std::chrono::minutes;

	struct HourMinute {
	// Represents a duration from Midnight (00:00)
	// 24 hours: to represent 8:30 AM
	// hour = 8, minute = 30
	// to represent 5:33 PM
	// hour = 17, minute = 33

	unsigned char hour;
	unsigned char minute;

	operator Duration () {
		return std::chrono::hours(hour) + std::chrono::minutes(minute);
	}
	};
}