#pragma once

//#include "../../Lib/date/date.h"
#include "TimeDuration.h"

namespace Model::Data {

	/// Public interface to an event. 
	struct Event {
		Model::Resources::Resource * mValue;
		date::year_month_day mDate;
		Time::HourMinute	 mStartTime;
		Time::Duration		 mDuration;
		Model::Properties::PropertyMapUniquePtr  mProperties;
	};

}