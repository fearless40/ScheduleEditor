#pragma once

#include "Range.h"
#include "Range.RawData.h"

namespace Model::Data::Range {

	// Holds a contiguous set of events that are seperated by days.
	// For instance of you have a list of days like so:
	// {1,2,3,5,6,7,8,9,15,16,20} it would be split into the following
	// d1 = {1,2,3}
	// d2 = {5,6,7,8,9}
	// d3 = {15, 16}
	// d4 = {20}
	// Hours to do not have to be contiguous 
	// This class is NOT a view but an actual container of the events
	// The class keeps the events by sorting them in order of time
	// Each set of events must have the same ResourceOwner
	class ContiguousDays {
		const Model::Data::DataModel & owner;

		// The range of dates in this Store
		Time::DateRange mDates;
		
		std::vector<RawEvent> mEvents;
		std::vector<Model::Properties::PropertyMap> mPropertyIndex;
		const Model::Resources::Resource * mResourceOwner;
		
	public:

		

		bool empty() const;

		class iterator_day {};
		class iterator_slot {};

		class const_iterator_day {};
		class const_iterator_slot {};

		Date date_start() const;
		Date date_end() const;

		iterator_day begin();
		iterator_day end();

		iterator_day operator[] (Date dt);
		iterator_day operator[] (uint32_t offset);

		const_iterator_day begin() const;
		const_iterator_day end() const;

		const_iterator_day operator[] (Date dt) const;
		const_iterator_day operator[] (uint32_t offset) const;

		iterator_day at(Date dt);
		iterator_day at(uint32_t offset);

		const_iterator_day at(Date dt) const;
		const_iterator_day at(uint32_t offset) const;

		Model::Data::Range::View	 at(Date start, Date end) const;
		Model::Data::Range::View	 view_get(Date start, Date end) const;
		
		const_iterator_slot slots(Date dt) const;
		const_iterator_slot slots(uint32_t offset) const;

		const_iterator_slot begin_slots() const;
		const_iterator_slot end_slots() const;

		iterator_slot slots(Date dt);
		iterator_slot slots(uint32_t offset);

		iterator_slot begin_slots();
		iterator_slot end_slots();
	};
}