#pragma once

//#include "../../Lib/date/date.h"
#include "TimeDuration.h"
#include "Data.Detail\Event.h"

namespace Model::Data {

	/// Public interface to an event. Only difference is it does not hold a unique pointer 
	// as this class is used by client code in a read only manner mostly
	class Event {
		EventHandle mHandle;
		Time::HourMinute	 mStartTime;
		Time::Duration		 mDuration;
		Model::Resources::Resource * mValue;
		Model::Properties::PropertyMap*   mProperties; //non owner

	public:
		Event() {}
		~Event() {}

		Event(EventHandle handle, Time::HourMinute start, Time::Duration dur, Model::Resources::Resource * res, Model::Properties::PropertyMap * map) :
			mHandle(handle),
			mStartTime(start),
			mDuration(dur),
			mValue(res),
			mProperties(map) {}

		Event(Event && evt) = default;
		Event(const Event & evt) = default;
		Event & operator = (const Event & evt) = default;
		
		// Getters
		date::year_month_day date() const noexcept { return mHandle; }
		Time::HourMinute start_time() const noexcept { return mStartTime; }
		Time::Duration duration() const noexcept { return mDuration; }
		Model::Resources::Resource * resource() const noexcept { return mValue; }
		Model::Properties::PropertyMap * properties() const noexcept { reutrn mProperties; }

		// No setters for now will consider in the future

	};

}