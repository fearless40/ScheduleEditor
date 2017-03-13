#pragma once

#include "Slots.h"

class Model::Properties::PropertyTemplate;

namespace Model::Slots {
	
	/// A collection of Slot. Items within are strongly ordered
	class SlotGroup {
		//Index mIndex;
		//using Slots = std::vector<Slot>;

		//Slots mSlots;
	public:
		
		class iterator {};
		class const_iterator {};
		
		/// Checks if the group of slots are organized based on start time
		bool timeBasedOrdering() const;

		/// Changes the time based ordering. If not time based then slots are organized by position only
		/// <remarks> If set to true it will re-sort the array </remarks>
		void timeBasedOrdering(bool value);

		// Get and set the name
		const std::string & name() const;
		void name(std::string newname);
		
		std::size_t count() const;

		const_iterator begin() const;
		const_iterator end() const;

		iterator begin();
		iterator end();

		const Slot & operator [] (uint32_t index) const;
		Slot & operator [] (uint32_t index);

		void insert(const_iterator before, const Slot & slot);
		void push_back(const Slot & slot);

		void remove(const_iterator slot);
		
		const Model::Properties::PropertyTemplate & propertyTemplate() const;

	};
}