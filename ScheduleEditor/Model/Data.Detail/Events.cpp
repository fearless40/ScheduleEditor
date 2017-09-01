#include "pch.h"
#include <memory>
#include <algorithm>
#include <numeric>
#include "../Resources.Resource.h"
#include "../Properties.PropertyMap.h"
#include "../Data.Event.h"
#include "Event.h"
#include "Events.h"
#include "EventsEditor.h"
#include "../Data.Event.h"
#include "../Data.DataStore.h"

using namespace Model::Data::Detail;

void Model::Data::Detail::Events::sort()
{
	std::sort(mData.begin(), mData.end());
}

Model::Data::Detail::Events::Events(Data::DataStore & owner) : mOwner(owner)
{

}

Model::Data::Detail::Events::~Events()
{
}

const Event * Model::Data::Detail::Events::find(EventHandle evt) const
{
	auto ret_iterator = std::lower_bound(mData.begin(), mData.end(), evt);
	if (ret_iterator->handle == evt) {
		return &(*ret_iterator);
	}

	return nullptr;
}

const bool Model::Data::Detail::Events::has(EventHandle evt) const
{
	return find(evt) == nullptr ? false : true;
}

Model::Data::Detail::Events::const_iterator Model::Data::Detail::Events::begin_date(date::year_month_day day) const
{
	return std::lower_bound(mData.cbegin(), mData.cend(), day);
}

Model::Data::Detail::Events::const_iterator Model::Data::Detail::Events::end_date(date::year_month_day day) const
{
	return std::upper_bound(mData.cbegin(), mData.cend(), day);
}

int Model::Data::Detail::Events::NbrDays() const
{
	date::year_month_day first = mData.front().handle;
	return std::accumulate(mData.cbegin(), mData.cend(), 0, [&first](const int v, const Event & e) {
		if (e.handle.fields.year == first.year && e.handle.fields.month == first.month && e.handle.fields.day == first.day) {
			return 0;
		} 
		else {
			first = e.handle;
			return 1;
		}
	});
}

bool Model::Data::Detail::Events::lock_read()
{
	return false;
}

void Model::Data::Detail::Events::unlock_read()
{
}

bool Model::Data::Detail::Events::lock_write()
{
	return false;
}

void Model::Data::Detail::Events::unlock_write()
{
}

EventHandle Model::Data::Detail::Events::make_unique_handle(date::year_month_day day, Time::HourMinute start) const
{
	EventHandle ret = make_handle(day, start);
	while (has(ret) == true) {
		++ret.fields.minute;
	}
	return ret;
}

EventsEditor Model::Data::Detail::Events::edit() const
{
	return EventsEditor(*const_cast<Events *>(this));
}

