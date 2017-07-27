#pragma once

#include "Model.h"
#include "Slots.h"
#include "Slots.Slot.h"
#include "Properties.HasProperties.h"

namespace Model::Slots {
	
	/// A collection of Slot. Items within are strongly ordered
	// The items in the vector can be passed by value. They are pretty light weight objects, this allows
	// a vector to be used in the class.
	// Each slot has a unique ID given by the class. It is NOT serialized and the ID is generated each time. 
	// The ID would need to be synced across the network though. The ID is mostly for find and remove features. 
	
	class SlotGroup : public Properties::HasProperties {
		Model::Index mIndex;
		using Slots = std::vector<Slot>;

		Slots mSlots;
	public:

		Model::Index index() const { return mIndex; }

		std::size_t count() const { return mSlots.size(); }

		auto begin() const { 
			return mSlots.cbegin();
		}
		auto end() const { return mSlots.cend(); }

		auto begin() { return mSlots.begin(); }
		auto end() { return mSlots.end();  }

		const Slot operator [] (std::size_t tindex) const { return mSlots[tindex]; }
		Slot operator [] (std::size_t tindex) { return mSlots[tindex]; }

		void remove(const Slot & slot);
		void remove(Slots::iterator it);
		void remove(Slot::SlotID id);
		Slot create();
		Slot create(std::string_view name);
		Slot create(Time::HourMinute start, Time::Duration duration);
		Slot create(std::string_view name, Time::HourMinute start, Time::Duration duration);
		void save(Slot slot);

	};
}