#pragma once


#include "Model.h"

class model::details::Events;

namespace model {
	
	class Schedule {
		
		model::Index mIndex;
		model::details::Events * mEvents;

		model::string mUserName; 

		bool mIsAllSaved; 
		bool mHasUnloadedData;

	public:
	
		const model::IndexConst getIndex() const noexcept { return model::IndexConst{ mIndex }; }
		const model::string_view getUserName() const noexcept { return model::string_view{ mUserName }; }

		getMonth(date::year year, date::month month);
		getYear(date::year year);
		getDates(date::year_month_day start, date::year_month_day end);
		getDay(date::year_month_day day);


	};
}