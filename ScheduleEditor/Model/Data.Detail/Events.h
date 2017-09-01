#pragma once
#include "Event.h"

class Model::Data::DataStore;

namespace Model::Data::Detail {

	class EventsEditor;

	/// Holds a list of events sorted by date
	class Events {
		std::vector<Event> mData;
		//Read lock
		//Write lock

		Model::Data::DataStore & mOwner; 

		void sort();

	public:
		using iterator = std::vector<Event>::iterator;
		using const_iterator = std::vector<Event>::const_iterator;

		Events(Model::Data::DataStore & owner);
		~Events();

		// Const Interface
		const Event * find(EventHandle evt) const;
		const bool	has(EventHandle evt) const;

		const_iterator begin_date(date::year_month_day day) const;
		// Works like a standard iterator (1 beyond the requested value)
		const_iterator end_date(date::year_month_day day) const;



		//Information functions
		date::year_month_day date_start() const { return mData.front().handle; }
		date::year_month_day date_last() const { return mData.back().handle; }
		std::size_t size() const { return mData.size(); }
		int NbrDays() const; 

		// Iteration
		auto begin() const { return mData.cbegin(); }
		auto end() const { return mData.cend(); }

		//auto begin() { return data.begin(); }
		//auto end() { return data.end(); }

		bool lock_read();
		void unlock_read();

		bool lock_write();
		void unlock_write();

		EventHandle make_unique_handle(date::year_month_day day, Time::HourMinute start) const;
		
		// Use the view classes to find stuff
		EventsEditor edit() const; 
	};
}
