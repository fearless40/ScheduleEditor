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

	class Slot {
	protected:
		Index	mIndex;
		long	mSlotID;
		Properties::PropertyMap mProperty;
	};
	
	class SlotTime : public Slot {
		TimeOnly mStart;
		TimeOnly mEnd;
		
	};

	class SlotCustom : public Slot {
		std::string mName;
	};

	template <typename T>
	class SlotGroup {
		Index mIndex;
		using Slots = std::vector<T>;

		Slots mSlots;
	public:
		void add(T & value);
		std::size_t count() const;

		operator (SlotGroup<Slot>)() {}

	};
}