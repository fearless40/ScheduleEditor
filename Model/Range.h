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
		const model::Schedule & mmodel;

	public:

		using const_iterator =  model::event::Events::const_iterator;

		//const model::Data::Datamodel & model() const noexcept { return mmodel; }

		bool empty() const noexcept { return mStart.value == 0 || mEnd.value == 0; }

		date::year_month_day date_start() const noexcept;
		date::year_month_day date_end() const noexcept;

		std::size_t count() const;

		const_iterator begin() const {
			return ;
		}
		const_iterator end() const {
			return;
		}



	};
}