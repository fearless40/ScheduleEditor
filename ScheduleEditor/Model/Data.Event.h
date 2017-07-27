#pragma once

namespace Model::Data {

	/// Public interface to an event. This is used between the program and the DataLayer
	class Event {
		Model::Resources::Resource * mValue;
		date::year_month_day mDate;
		Time::HourMinute	 mStartTime;
		Time::Duration		 mDuration;
		Model::Properties::PropertyMap * mProperties;
	};

}