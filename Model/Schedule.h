#pragma once


#include "Model.h"
#include "event\Events.h"
#include "Range.h"
#include "event\EventDiff.h"

class model::details::Events;

namespace model {
	
	class Schedule {
		
		std::unique_ptr< model::event::EventDiff > mHistory;
		std::unique_ptr<model::event::Events> mCurrent;

		model::Index mIndex;
		model::string mUserName; 

		bool mIsAllSaved; 
		bool mHasUnloadedData;
		
	public:
	
		const model::IndexConst getIndex() const noexcept { return model::IndexConst{ mIndex }; }
		const model::string_view getUserName() const noexcept { return model::string_view{ mUserName }; }

		const model::event::Events & current() const noexcept;

		Range all() const noexcept; 
		Range month(date::year year, date::month month) const noexcept;
		Range year(date::year year) const noexcept;
		Range between(date::year_month_day start, date::year_month_day end) const noexcept;
		Range day(date::year_month_day day) const noexcept;

		void history_add(std::unique_ptr<model::event::Events> currentEvents, std::unique_ptr<model::event::EventDiff> diff) {
			if (mHistory) {
				diff->prior_set(std::move(mHistory));
			} 
			else {
				diff->prior_set(std::move(mCurrent));
			}
			mHistory = std::move(diff);
			mCurrent = std::move(currentEvents);
		}

		void history_clear() {
			if (mHistory) {
				mHistory.release();
			}
		}
	};
}