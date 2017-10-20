#include "pch.h"
#include <memory>
#include <algorithm>
#include <numeric>
#include "../Resources.Resource.h"
#include "../Properties.PropertyMap.h"
#include "../Data.Event.h"
#include "EventsEditor.h"

#include "Event.h"
#include "Events.h"
#include "../Data.Event.h"


using namespace Model::Data::Detail;

void Model::Data::Detail::Events::sort()
{
	std::sort(mData.begin(), mData.end());
}


Events::const_iterator Events::find_iterator(EventHandle evt) const
{
	auto ret_iterator = std::lower_bound(mData.begin(), mData.end(), evt);
	if (ret_iterator != mData.end() && ret_iterator->handle == evt) {
		return ret_iterator;
	}

	return mData.end();
}

Events::iterator Events::find_iterator(EventHandle evt)
{
	auto ret_iterator = std::lower_bound(mData.begin(), mData.end(), evt);
	if (ret_iterator != mData.end() && ret_iterator->handle == evt) {
		return ret_iterator;
	}

	return mData.end();
}

const Event * Model::Data::Detail::Events::find(EventHandle evt) const
{
	auto ret_iterator = std::lower_bound(mData.begin(), mData.end(), evt);
	if (ret_iterator != mData.end() && ret_iterator->handle == evt) {
		return &(*ret_iterator);
	}

	return nullptr;
}

Event * Model::Data::Detail::Events::find(EventHandle evt) 
{
	auto ret_iterator = std::lower_bound(mData.begin(), mData.end(), evt);
	if (ret_iterator != mData.end()  && ret_iterator->handle == evt) {
		return &(*ret_iterator);
	}

	return nullptr;
}


const bool Model::Data::Detail::Events::has(EventHandle evt) const
{
	return find(evt) == nullptr ? false : true;
}

Events::const_iterator Events::begin_date(date::year_month_day day) const
{
	return std::lower_bound(mData.cbegin(), mData.cend(), day);
}

Events::const_iterator Events::end_date(date::year_month_day day) const
{
	return std::upper_bound(mData.cbegin(), mData.cend(), day);
}

Events::iterator Events::begin_date(date::year_month_day day) 
{
	return std::lower_bound(mData.begin(), mData.end(), day);
}

Events::iterator Events::end_date(date::year_month_day day) 
{
	return std::upper_bound(mData.begin(), mData.end(), day);
}


int Model::Data::Detail::Events::NbrDays() const
{
	date::year_month_day first = mData.front().handle;
	return std::accumulate(mData.cbegin(), mData.cend(), 0, [&first](const int v, const Event & e) {
		if (e.handle.fields.year == (uint32_t)(int)first.year() && e.handle.fields.month == (uint32_t)first.month() && e.handle.fields.day == (uint32_t)first.day()) {
			return 0;
		} 
		else {
			first = e.handle;
			return 1;
		}
	});
}

bool Model::Data::Detail::Events::lock_read() const
{
	return false;
}

void Model::Data::Detail::Events::unlock_read() const
{
}

bool Model::Data::Detail::Events::lock_write()
{
	return false;
}

void Model::Data::Detail::Events::unlock_write(bool dataChanged)
{
	if (dataChanged)
		sort();
}

EventHandle Model::Data::Detail::Events::make_unique_handle(date::year_month_day day, Time::HourMinute start) const
{
	EventHandle ret = make_handle(day, start);
	while (has(ret) == true) {
		++ret.fields.minute;
	}
	return ret;
}

EventsEditor Events::edit() const
{
	return EventsEditor(*const_cast<Events *>(this));
}

