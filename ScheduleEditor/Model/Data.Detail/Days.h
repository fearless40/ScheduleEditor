#pragma once

namespace Model::Data::Detail {
	
	/// Holds the days in a Month
	class Days {
		date::month mMonth;
		std::vector<DayEvents> mDays;

	public:
		// Event helper
		const Event * event_find(EventHandle evt) const;

		// Day finder
		const DayEvents * find(date::day d) const;
		bool  has(date::day d) const;

		// Informational 
		date::month month() const noexcept;
		date::day	first() const;
		date::day	last()	const;
		date::days	span() const;

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