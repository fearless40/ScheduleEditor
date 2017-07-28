#pragma once

namespace Model::Data::Detail {
	
	/// Holds the events in a Day
	class DayEvents {
		data::day mDay;
		std::vector<DataStore::Event> mEvents;

	public:
		// Event find interface
		const Event * event_find(EventHandle evt) const;

		// Finder
		const Event * find(EventHandle evt) const;
		bool  has(EventHandle evt) const;

		// Informational 
		data::day	day() const noexcept;
		EventHandle first() const;
		EventHandle last() const;
		
		// Interator interface
		auto begin() const;
		auto end() const;

		// Edit interface
		SomeType edit() const;

		// Lockable interface
		bool lock(LockType type);
		void unlock(LockType type);

		// Sorting interface
		void sort();

	};
}