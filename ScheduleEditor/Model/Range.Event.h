#pragma once

namespace Model::Range {

	/// Public interface to use to access Ranges. A range holds a set of Events
	class Event {
		Model::Resources::Resource * mValue;
		date::sys_days		mDate;
		Time::HourMinute	mStartTime;
		Time::Duration		mDuration;
		Model::Slots::Slot::SlotID mSlotID_Start;
		Model::Slots::Slot::SlotID mSlotID_End;

	public:

	};

}