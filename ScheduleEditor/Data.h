#pragma once



namespace Model::Data {
	enum class Duration {
		Month,
		Week,
		Day
	};

	/// Range only supports contigous ranges of data. You cannot merge two discontinous ranges
	/// The range implements a single dimensional array but simulates a two dimensional array
	/// Ranges need a SlotGroup associated with them.
	/*class Range {
		TimePoint mStart;
		TimePoint mEnd;

		// Currently not used
		//Duration mDurations;
		
		const SlotGroup<Slot> * mSlots;
		std::vector<const Resource *> mData;

	public:
		operator const Resource * (TimePoint tm);
	};*/



	class Data {
		//Duration mDurations;
		

	};
}