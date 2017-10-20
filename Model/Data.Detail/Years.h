#pragma once 

#include <vector>
#include <../../../Lib/date/date.h>
#include "Helpers.h"

namespace Model::Data::Detail {
	
	/// Holds years
	class Years {
		std::vector<Year> mYears;

	public:
		//Years();
		//~Years();

		class EditorLock : public ModifierT<Years>{
			EditorLock() = delete;
			
		public:
			EditorLock(Years & yr) : ModifierT(yr,LockType::Write) {};
			Year * add(date::year yr);
			void remove(date::year yr);
			void reserve(std::size_t nbrOfYears);
		};

		// Needed for the reserve function
		friend class EditorLock;

		// Event interface helper
		const Event	* event_find(EventHandle evt) const;

		// Year information interface
		const Year *	find(date::year y) const;
		bool			has(date::year y) const;

		date::year		first() const noexcept;
		date::year		last() const noexcept;
		//std::pair<date::year,date::year>		span() const noexcept;

		// Interator interface
		auto begin() const { return mYears.cbegin(); }
		auto end() const { return mYears.cend(); }

		// Edit interface
		EditorLock edit() const;

		// Lockable interface
		bool lock(LockType type);
		void unlock(LockType type);

		// Sorting interface
		void sort();

	};
}