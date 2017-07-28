#include "pch.h"
#include <algorithm>
#include "Event.h"
#include "Months.h"
#include "Years.h"

using namespace Model::Data::Detail;

const Event * Years::event_find(EventHandle evt) const
{
	auto month = find(date::year(evt.fields.year));
	if (month) {
		return month->event_find(evt);
	}
	else {
		return nullptr;
	}
}

const Months * Model::Data::Detail::Years::find(date::year y) const
{
	auto it = std::lower_bound(begin(), end(), y);
	if (it != end() && it->year() == y) {
		return &*it;
	}
	else {
		return nullptr;
	}
}

bool Model::Data::Detail::Years::has(date::year y) const
{
	if (find(y)) {
		return true;
	}
	return false;
}

date::year Model::Data::Detail::Years::first() const noexcept
{
	return mYears.front().year();
}

date::year Model::Data::Detail::Years::last() const noexcept
{
	return mYears.back().year();
}

bool Model::Data::Detail::Years::lock(LockType type)
{
	return true;
}

void Model::Data::Detail::Years::unlock(LockType type)
{
}

void Model::Data::Detail::Years::sort()
{
	std::sort(mYears.begin(), mYears.end());
}







