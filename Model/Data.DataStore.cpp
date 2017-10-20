#include "pch.h"
#include <optional>
#include <array>
#include <algorithm>
#include "TimeDuration.h"
#include "Properties.PropertyMap.h"
#include "Data.DataStore.h"
#include "Data.RawEvents.h"

namespace Model::Data {

	using Event = DataStore::Event;
	using EventHandle = DataStore::EventHandle;
	using Year = uint16_t;
	using Month = unsigned char;
	using Day = unsigned char;

	namespace Detail {
		template<typename LockAble > 
		class ModifierT {
			bool mIsValid{ false; }
			bool mChanged{ false; }
			LockAble & owner;
		public:
			ModifierT(LockAble & t) : owner(t) {
				mIsValid = owner.lock();
			}
			~ModifierT() {
				if (mIsValid && mChanged) {
					owner.sort();
				}
				if (mIsValid)
				{
					owner.unlock();
				}
			}
			bool isValid() const { return mIsValid; }
			bool hasChanged() const { return mChanged; }
		};
	}

	class DayEvents {

		Day mDay{ 255 };
		std::vector<DataStore::Event> mEvents;

	
	public:
		DayEvents() { };
		DayEvents(unsigned char day) : mDay(day) {}

		class Modifier : public Detail::ModifierT<DayEvents> {
		public:
			EventHandle add(DataStore::Event & evt);
			void remove(EventHandle & evt);
			void remove(DataStore::Event & evt);
			EventHandle change(EventHandle eHandle, DataStore::Event & evt);
		};

		/// Sorts the data by EventHandle
		void sort();

		/// Returns false if can't get the lock
		bool lock();

		/// Unlocks the array
		void unlock();

		/// Finds an event
		std::optional<DataStore::Event> find(EventHandle eHandle) const;

		auto begin() const { return mEvents.cbegin(); }
		auto end() const { return mEvents.cend(); }

		bool isDayEmpty() const;

		std::size_t size() const;

		/// If the class is locked already it will not able to return a Modifier so return an empty value
		/// marked as const as otherwise could never edit the data
		std::optional<Modifier> edit() const;

		Day day_get() const { return mDay; }

	};

	bool operator < (const DayEvents & d1, const DayEvents & d2) {
		return d1.day_get() < d2.day_get();
	}

	bool operator < (const DayEvents & d1, Day d) {
		return d1.day_get() < d;
	}

	bool operator < (Day d, const DayEvents & d1) {
		return d < d1.day_get();
	}



	class MonthIndex {
		//Month mMonth{ 255 }; // Does not need to keep track of what month it self is
		std::vector<DayEvents> mDays;
		
	public:

		// Const iterators
		auto begin() const { return mDays.cbegin(); }
		auto end() const { return mDays.cend(); }

		bool empty() const { return mDays.empty(); }

		void sort() {
			std::sort(mDays.begin(), mDays.end());
		}

		// Does nothing for now
		bool lock() {
			return true;
		}
		void unlock() {

		}

		bool has(Day d) const {
			auto it = std::lower_bound(begin(), end(), d);
			if (it == end()) {
				return false;
			}
			if (it->day_get() == d) {
				return true;
			}
			return false;
		}

		std::optional<const DayEvents &> get(Day d) const {
			auto it = std::lower_bound(begin(), end(), d);
			if (it == end()) {
				return {};
			}
			if (it->day_get() == d) {
				return *it;
			}
			return {};
		}
		 
	};


	// Very simple and does not need a modification class as the data elements are always in a fixed location
	struct YearIndex {
		Year year;
		std::array<MonthIndex, 12> months;

		const MonthIndex * month_get(Month m) const {
			--m;
			if (m < 0 || m > 11) {
				return nullptr;
			}
			return &months[m];
		}
		
		bool month_has_data(Month m) const {
			auto mon = month_get(m);
			if (mon) {
				return mon->empty();
			}
			else {
				return false;
			}
		}

	};


	class EventIndex {
		std::vector<YearIndex> mYears;

	public:
		class Modifier;

		// Const_Iterators
		auto begin() const { return mYears.cbegin(); }
		auto end() const { return mYears.cend(); }

		// Informational functions
		Year year_start() const;
		Year year_end() const;
		bool year_has(Year yr) const;
		bool year_has(date::year_month_day dt) const;
		bool date_has(date::year_month_day dt) const;

		
		const YearIndex * find(Year yr) const {
			auto it = std::lower_bound(begin(), end(), yr);
			if (it == end()) {
				return nullptr;
			}
			else if (it->year == yr) {
				return &*it;
			}
		}

		bool has(Year yr) const {
			if (find(yr))
				return true;
		}

		const YearIndex * get(Year yr) const {
			return find(yr);
		}

		std::optional<const Event &> event_from_handle(EventHandle eHandle);
		// Array information functions
		//std::vector<Event> get_events()

		


		// Special member functions
		void sort();

		void unlock();
		bool lock();


		class Modifier {
			bool mChanged{ false };
			bool mIsValid{ false };
			EventIndex & owner;

		public:
			Modifier(EventIndex & o) : owner(o) {
				mIsValid = owner.lock();
			}

			~Modifier() {
				if (mChanged && mIsValid)
					owner.sort();

				if (mIsValid)
					owner.unlock();
			}

			bool isValid() const{ return mIsValid; }

			EventHandle add(const Data::RawEvent & evt, Model::Properties::PropertyMap * pmap) {
				
				// Semi pseudo code for now
				date::year_month_day dm{ evt.date };

				auto item = owner.find(dm.year);
				if (item) {
					auto mitem = item->month_get(dm.month);
					if (mitem->has(dm.day)) {
						mitem.edit().add()
					}
				}

				
			}
			void remove(EventHandle evt);
			EventHandle change(EventHandle eHandle, Event & evt);
		};
	};
}