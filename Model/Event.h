#pragma once

//#include "../../Lib/date/date.h"
#include "timeDuration.h"
#include "Data.Detail\Event.h"

class model::Resources::Resource;
class model::Properties::PropertyMap;

namespace model {

	/// Public interface to an event. Only difference is it does not hold a unique pointer 
	// as this class is used by client code in a read only manner mostly
	class Event {
		model::details::EventHandle mHandle;
		time::HourMinute	 mStarttime;
		time::Duration		 mDuration;
		model::Resources::Resource * mValue;
		model::Properties::PropertyMap*   mProperties; //non owner

	public:
		Event() {}
		~Event() {}

		Event(model::Data::Detail::EventHandle handle, time::HourMinute start, time::Duration dur, model::Resources::Resource * res, model::Properties::PropertyMap * map) :
			mHandle(handle),
			mStarttime(start),
			mDuration(dur),
			mValue(res),
			mProperties(map) {}

		Event(Event && evt) = default;
		Event(const Event & evt) = default;
		Event & operator = (const Event & evt) = default;
		
		// Getters
		date::year_month_day date() const noexcept { return mHandle; }
		time::HourMinute start_time() const noexcept { return mStarttime; }
		time::Duration duration() const noexcept { return mDuration; }
		model::Resources::Resource * resource() const noexcept { return mValue; }
		model::Properties::PropertyMap * properties() const noexcept { return mProperties; }

		// No setters for now will consider in the future

	};

}