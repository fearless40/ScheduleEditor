#pragma once

#include "TimeDuration.h"

namespace Model::Slots {


	/// Public helper struct used in SlotGroup
	struct Slot 
	{
		using SlotID = uint32_t;
		std::string name_display;
		Time::HourMinute start_time;
		Time::Duration duration;
	
		Slot() = default;
		Slot(Slot &&) = default;
		Slot(const Slot &) = default;
		Slot(uint32_t id) : mID(id) {}
		Slot(uint32_t id, Time::HourMinute hm, Time::Duration d) : mID(id), start_time(hm), duration(d) {}
		Slot(uint32_t id, Time::HourMinute hm, Time::Duration d, std::string_view name) : mID(id), start_time(hm), duration(d), name_display(name) {}

		
	/*	Time::HourMinute start() const;
		void start(Time::HourMinute tm);

		Model::Time::Duration duration() const;
		void duraton(Time::Duration length);

		std::string_view name() const { return mDisplayName;  }
		void name_set(std::string_view newname) {
			mDisplayName = newname;
		}
		*/

		SlotID id() const { return mID;  }

	private:
		SlotID mID{ 0 };
		
	};
}
