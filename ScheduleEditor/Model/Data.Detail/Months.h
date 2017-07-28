#pragma once 

namespace Model::Data::Detail {
	
	/// Holds the months in a year
	class Months {
		date::year mYear;
		std::array<Days, 12> mMonths;

	public:
		//Months();
		//~Months();

		// Event interface helper
		const Event * event_find(EventHandle evt) const;

		// Day finder
		const Days * find(date::month m) const;
		bool has(date::month m) const;

		// Information
		date::year	year() const noexcept;
		date::month	first() const noexcept;
		date::month last() const noexcept;
		date::months span() const noexcept;
		
		// Interator interface
		auto begin() const;
		auto end() const;

		// Edit interface
		SomeType edit() const;

		// Lockable interface
		bool lock(LockType type);
		void unlock(LockType type);

		// Sorting interface
		// In this class does nothing but if the implementation changes it may switch to doing something!
		void sort(); 
	};
}