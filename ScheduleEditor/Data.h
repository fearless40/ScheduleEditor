#pragma once

namespace Model::Data {
	enum class Duration {
		Month,
		Week,
		Day
	};

	struct EventTime {
		Event * event;
		Time start;
		Time end;
	};
	
	class Range {
		TimePoint start;
		TimePoint end;
		Event * events;
		long mNbrTimeDivisions;
	};



	class Data {
		Duration mDurations;
		SlotGroup slots;

	};
}