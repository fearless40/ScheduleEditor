#pragma once 

#include <vector>
#include <../../../Lib/date/date.h>
#include "Helpers.h"

namespace Model::Data::Detail {
	
	/// Holds years
	class Years {
		std::vector<Months> mYears;

	public:
		//Years();
		//~Years();

		// Event interface helper
		const Event	* event_find(EventHandle evt) const;

		// Year information interface
		const Months *	find(date::year y) const;
		bool			has(date::year y) const;

		date::year		first() const noexcept;
		date::year		last() const noexcept;
		date::years		span() const noexcept;

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