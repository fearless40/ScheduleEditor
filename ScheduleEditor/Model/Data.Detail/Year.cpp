#include "pch.h"
#include <algorithm>
#include "../Resources.Resource.h"
#include "../Properties.PropertyMap.h"
#include "Helpers.h"
#include "Event.h"
#include "Day.h"
#include "Month.h"
#include "Year.h"

using namespace Model::Data::Detail;

const Event * Model::Data::Detail::Year::event_find(EventHandle evt) const
{
	auto month = find(date::month(evt.fields.month));
	if (month) {
		return month->event_find(evt);
	}
	else {
		return nullptr;
	}
}

const Month * Model::Data::Detail::Year::find(date::month m) const
{
	if (static_cast<unsigned>(m) < 1 && static_cast<unsigned>(m) > 12)
		return nullptr;

	size_t pos = static_cast<unsigned>(m) - 1;

	return &mMonths[pos];
}

bool Model::Data::Detail::Year::has(date::month m) const
{
	return find(m) ? true : false;
}

date::year Model::Data::Detail::Year::year() const noexcept
{
	return mYear;
}

date::month Model::Data::Detail::Year::first() const noexcept
{
	return date::month(1);
}

date::month Model::Data::Detail::Year::last() const noexcept
{
	return date::month(12);
}


Model::Data::Detail::Year::Editor Model::Data::Detail::Year::edit() const
{
	return Year::Editor(*const_cast<Year*>(this));
}

bool Model::Data::Detail::Year::lock(LockType type)
{
	return true;
}

void Model::Data::Detail::Year::unlock(LockType type)
{
}

void Model::Data::Detail::Year::sort()
{
	// Does nothing data is already sorted
}

Month * Model::Data::Detail::Year::Editor::add(date::month mt)
{
	auto month = owner.find(mt);
	if (month) {
		if (static_cast<unsigned>(month->month()) == 0u) {
			auto pos = static_cast<unsigned>(mt) - 1u;
			owner.mMonths[pos] = Month(mt);
		}
		return const_cast<Month*>(month);
	}
	else { return nullptr; }
}

void Model::Data::Detail::Year::Editor::remove(date::month mt)
{
	auto month = owner.find(mt);
	if (month) {
		if (static_cast<unsigned>(month->month()) != 0u) {
			auto pos = static_cast<unsigned>(mt) - 1u;
			owner.mMonths[pos] = Month();
		}
	}
}

void Model::Data::Detail::Year::Editor::reserve(std::size_t sz)
{
	// Do nothing
}