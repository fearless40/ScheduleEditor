#pragma once

#include "timeDuration.h"

namespace model::Slots {


	/// Public helper struct used in SlotGroup
	struct Slot 
	{
		using SlotID = uint32_t;
		std::string name_display;
		time::HourMinute start_time;
		time::Duration duration;
	
		Slot() = default;
		Slot(Slot &&) = default;
		Slot(const Slot &) = default;
		Slot(uint32_t id) : mID(id) {}
		Slot(uint32_t id, time::HourMinute hm, time::Duration d) : mID(id), start_time(hm), duration(d) {}
		Slot(uint32_t id, time::HourMinute hm, time::Duration d, std::string_view name) : mID(id), start_time(hm), duration(d), name_display(name) {}

		
	/*	time::HourMinute start() const;
		void start(time::HourMinute tm);

		model::time::Duration duration() const;
		void duraton(time::Duration length);

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
