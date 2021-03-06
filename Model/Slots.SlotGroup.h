#pragma once

#include "model.h"
#include "Slots.h"
#include "Slots.Slot.h"
//#include "Properties.HasProperties.h"

namespace model::Slots {
	
	/// A collection of Slot. Items within are strongly ordered
	// The items in the vector can be passed by value. They are pretty light weight objects, this allows
	// a vector to be used in the class.
	// Each slot has a unique ID given by the class. It is NOT serialized and the ID is generated each time. 
	// The ID would need to be synced across the network though. The ID is mostly for find and remove features. 
	
	class SlotGroup {// public Properties::HasProperties {
		model::Index mIndex;
		using Slots = std::vector<Slot>;

		Slots mSlots;
	public:

		using const_iterator = Slots::const_iterator;
		using iterator = Slots::iterator;

		model::Index index() const { return mIndex; }

		std::size_t count() const { return mSlots.size(); }

		auto begin() const { return mSlots.cbegin(); }
		auto end() const { return mSlots.cend(); }

		auto begin() { return mSlots.begin(); }
		auto end() { return mSlots.end();  }
		
		const Slot operator [] (std::size_t tindex) const { return mSlots[tindex]; }
		Slot operator [] (std::size_t tindex) { return mSlots[tindex]; }

		void remove(const Slot & slot);
		void remove(Slots::iterator it);
		void remove(Slot::SlotID id);
		const Slot & create(time::HourMinute start, time::Duration duration);
		const Slot & create(std::string_view name, time::HourMinute start, time::Duration duration);
		
	};
}