#pragma once

//#include "../../Lib/boost/boost/iterator/transform_iterator.hpp"
#include "event\Events.h"
#include "event\Event.h"
#include "Schedule.h"

namespace model {

	
	/// A view into a Data. Lightweight class pass by value. 
	/// Always const cannot edit data.
	class Range {
		model::event::EventHandle mStart{ 0 };
		model::event::EventHandle mEnd{ 0 };
		//const model::event::Events & mEvents;
		model::Schedule & mSchedule;

	public:

		using const_iterator =  model::event::Events::const_iterator;

		model::Schedule & schedule() noexcept { return mSchedule; }

		bool empty() const noexcept { return mStart.value == 0 || mEnd.value == 0; }

		date::year_month_day date_start() const noexcept { return begin()->date(); }
		date::year_month_day date_end() const noexcept { return (end() - 1)->date(); }

		std::size_t count() const { return std::distance(begin(), end()); }

		const_iterator begin() const {
			return mSchedule.current().find_iterator(mStart);
		}

		const_iterator end() const {
			return mSchedule.current().find_iterator(mEnd);
		}
	};
}