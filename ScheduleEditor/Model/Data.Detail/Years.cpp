#include "pch.h"
#include <algorithm>
#include "../Resources.Resource.h"
#include "../Properties.PropertyMap.h"
#include "Helpers.h"
#include "Event.h"
#include "Day.h"
#include "Month.h"
#include "Year.h"
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

const Year * Model::Data::Detail::Years::find(date::year y) const
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

Model::Data::Detail::Years::EditorLock Model::Data::Detail::Years::edit() const
{
	return Model::Data::Detail::Years::EditorLock( *const_cast<Years*>(this) );
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



// Editor Lock Code
// 
Year * Model::Data::Detail::Years::EditorLock::add(date::year yr)
{
	auto doesExist = owner.find(yr);
	if (doesExist) {
		return const_cast<Year*>(doesExist);
	}
	else {
		owner.mYears.emplace_back(yr);
	}
}

void Model::Data::Detail::Years::EditorLock::remove(date::year yr)
{
	// Assume that since we are adding things that it is not sorted so do a linear search
	std::remove_if(owner.mYears.begin(), owner.mYears.end(), [&yr](const auto & value) { return (value.year() == yr); });
}

void Model::Data::Detail::Years::EditorLock::reserve(std::size_t nbrOfYears)
{
	owner.mYears.reserve(nbrOfYears);
}
