#pragma once

namespace Model::Slots {


	/// Public helper struct used in SlotGroup
	struct Slot 
	{
		using SlotID = uint32_t;
		std::string mDisplayName;
		Time::HourMinute mStart;
		Time::Duration mDuration;
	
		Slot() = default;
		Slot(Slot &&) = default;
		Slot(const Slot &) = default;
		Slot(uint32_t id) : mID(id) {}
		Slot(uint32_t id, Time::HourMinute hm, Time::Duration d) : mID(id), mStart(hm), mDuration(d) {}
		Slot(uint32_t id, Time::HourMinute hm, Time::Duration d, std::string_view name) : mID(id), mStart(hm), mDuration(d), mDisplayName(name) {}

		
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
