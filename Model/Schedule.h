#pragma once


#include "Model.h"
#include "event\Events.h"
#include "Range.h"
#include "event\EventDiff.h"

class model::event::Events;

namespace model {
	class Range;

	class Schedule {
	public:
		using HistoryVector = std::vector<model::event::EventDiff>;
	
	private:

		model::event::Events mBeginHistory;
		model::event::Events mCurrent;
		HistoryVector mHistory;

		model::Index mIndex;
		model::string mUserName; 

		bool mIsAllSaved; 
		bool mHasUnloadedData;
		
	public:
		struct History {
			const std::vector<model::event::EventDiff> & history;
			const model::event::Events & initial;
			auto begin() { return history.rbegin(); }
			auto end() { return history.rend(); }
		};


		const model::IndexConst getIndex() const noexcept { return model::IndexConst{ mIndex }; }
		const model::string_view getUserName() const noexcept { return model::string_view{ mUserName }; }

		const model::event::Events & current() const { return mCurrent; }

		Range all() const noexcept; 
		Range month(date::year year, date::month month) const noexcept;
		Range year(date::year year) const noexcept;
		Range between(date::year_month_day start, date::year_month_day end) const noexcept;
		Range day(date::year_month_day day) const noexcept;

		model::event::EventsEditor edit() const;

		void changes_commit(model::event::EventsEditor && editor);
		void changes_commit_no_history(model::event::EventsEditor && editor);

		void history_clear();
		History history() {
			return { mHistory, mBeginHistory };
		}

		HistoryVector history_rollback(int depth);
		HistoryVector history_rollback(HistoryVector::const_iterator pos);
		void history_redo(HistoryVector && vec);
	};
}