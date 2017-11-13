#pragma once
#include "Event.h"


namespace model::event {

	class EventsEditor;

	/// Holds a list of events sorted by date
	class Events {
		std::vector<Event> mData;
		//Read lock
		//Write lock

		

	public:
		using iterator = std::vector<Event>::iterator;
		using const_iterator = std::vector<Event>::const_iterator;

		// Const Interface
		const Event * find(EventHandle evt) const;
		const bool	has(EventHandle evt) const;
		const_iterator find_iterator(EventHandle evt) const;
		const_iterator begin_date(date::year_month_day day) const;
		// Works like a standard iterator (1 beyond the requested value)
		const_iterator end_date(date::year_month_day day) const;

		


		// Non const version
		Event * find(EventHandle evt);
		iterator begin_date(date::year_month_day day);
		iterator find_iterator(EventHandle evt);
		// Works like a standard iterator (1 beyond the requested value)
		iterator end_date(date::year_month_day day);

		std::vector<Event> & get() { return mData; }



		//Information functions
		date::year_month_day date_start() const { return mData.front().handle; }
		date::year_month_day date_last() const { return mData.back().handle; }
		std::size_t size() const { return mData.size(); }
		int count_days() const; 

		// Iteration
		auto begin() const { return mData.cbegin(); }
		auto end() const { return mData.cend(); }

		auto begin() { return mData.begin(); }
		auto end() { return mData.end(); }

		bool lock_read() const;
		void unlock_read() const;

		bool lock_write();
		void unlock_write(bool dataChanged = false);

		EventHandle make_unique_handle(date::year_month_day day, time::HourMinute start) const;
		
		// Use the view classes to find stuff
		EventsEditor edit() const; 

		void sort();
	};
}
