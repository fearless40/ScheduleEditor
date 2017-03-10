#pragma once



namespace Model::Slots {
	
	struct TimeOnly {
		// Represents a duration from Midnight (00:00)
		// 24 hours: to represent 8:30 AM
		// hour = 8, minute = 30
		// to represent 5:33 PM
		// hour = 17, minute = 33
		
		unsigned char hour;
		unsigned char minute;
	};

	/// A item that represents a time-period or organizing block
	/// Slots are strongly ordered represented by mSlotOrder
	class Slot {
	protected:
		Index	mIndex;
		long	mSlotOrder;
		Properties::PropertyMap mProperty;
		TimeOnly mStart;
		TimeOnly mEnd;
		const SlotGroup * const mOwner;
	};
	
	
	/// A collection of Slot. Items within are ordered by mSlotOrder
	class SlotGroup {
		Index mIndex;
		using Slots = std::vector<Slot>;

		Slots mSlots;
	public:
		void add(Slot & value);
		std::size_t count() const;

		

	};

	SlotGroup & Get(Index index);
	SlotGroup & Create(Index index);
}