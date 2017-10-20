#include "pch.h"
#include <algorithm>
#include "../Resources.Resource.h"
#include "../Properties.PropertyMap.h"
#include "Helpers.h"
#include "Event.h"
#include "Day.h"

using namespace Model::Data::Detail;

const Event * Model::Data::Detail::Day::event_find(EventHandle evt) const
{
	return find(evt);
}

const Event * Model::Data::Detail::Day::find(EventHandle evt) const
{
	auto item = std::lower_bound(mEvents.cbegin(), mEvents.cend(), evt);
	if (item != mEvents.end()) {
		if (*item == evt) {
			return &*item;
		}
	}
	return nullptr;
}

bool Model::Data::Detail::Day::has(EventHandle evt) const
{
	return find(evt) ? true : false;
}

date::day Model::Data::Detail::Day::day() const noexcept
{
	return mDay;
}

EventHandle Model::Data::Detail::Day::first() const
{
	return mEvents.front().handle;
}

EventHandle Model::Data::Detail::Day::last() const
{
	return mEvents.back().handle;
}

Model::Data::Detail::Day::Editor Model::Data::Detail::Day::edit() const
{
	return Model::Data::Detail::Day::Editor(*const_cast<Day*>(this));
}

bool Model::Data::Detail::Day::lock(LockType type)
{
	return true;
}

void Model::Data::Detail::Day::unlock(LockType type)
{
}

void Model::Data::Detail::Day::sort()
{
	std::sort(mEvents.begin(), mEvents.end());
}

Model::Data::Detail::Event * Model::Data::Detail::Day::Editor::add(unsigned short minutes_since_midnight)
{
	//Todo: write in code to create an event with a particular handle
	return nullptr;
}

void Model::Data::Detail::Day::Editor::remove(EventHandle evt)
{
	auto remove_it = std::remove(owner.mEvents.begin(), owner.mEvents.end(), evt);
	owner.mEvents.erase(remove_it);
}

void Model::Data::Detail::Day::Editor::reserve(std::size_t sz) {
	owner.mEvents.reserve(sz);
}
