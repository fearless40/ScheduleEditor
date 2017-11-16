#include "pch.h"
#include <algorithm>
#include <cassert>
#include "property\Map.h"
#include "EventsEditor.h"
#include "Events.h"
#include "resource\Value.h"
#include "Event.h"

using namespace model::event;

using Resource = model::resource::Value;

EventsEditor::EventsEditor(Events & evt) : mEvents(evt)
{
}

EventsEditor::~EventsEditor()
{
	if (AutoCommit) {
		changes_commit();
	}
}

EventHandle EventsEditor::new_handle(date::year_month_day day, model::time::HourMinute starttime) 
{
	EventHandle handle = mEvents.make_unique_handle(day, starttime);

	while (mExistingHandles.count(handle) == 1) {
		handle.fields.minute += 1;
	}
	
	mExistingHandles.insert(handle);

	return handle;
}

EventHandle EventsEditor::create(date::year_month_day day, model::time::HourMinute starttime, model::time::Duration length, const Resource * resource)
{
	Event evt;
	evt.handle = new_handle(day, starttime);
	evt.start = starttime;
	evt.value = resource;
	evt.minutes = length;
	
	mToBeAdded.push_back(std::move(evt));

	return mToBeAdded.back().handle;
}

EventHandle EventsEditor::create(date::year_month_day day, model::time::HourMinute starttime, model::time::Duration length, const Resource * resource, const model::property::Map & pmap)
{
	Event evt;
	evt.handle = new_handle(day, starttime);
	evt.start = starttime;
	evt.minutes = length;
	evt.value = resource;
	evt.properties = std::make_shared<model::property::Map>(pmap);

	mToBeAdded.push_back(std::move(evt));

	return mToBeAdded.back().handle;
}

EventHandle model::event::EventsEditor::create(date::year_month_day day, model::time::HourMinute starttime, model::time::Duration length, const model::resource::Value * resource, std::shared_ptr<const model::property::Map> pmap)
{
	Event evt;
	evt.handle = new_handle(day, starttime);
	evt.start = starttime;
	evt.minutes = length;
	evt.value = resource;
	evt.properties = pmap;

	mToBeAdded.push_back(std::move(evt));

	return mToBeAdded.back().handle;
}



EventHandle EventsEditor::create(const Event & evt)
{
	Event nevt{ evt };
	nevt.handle = new_handle(evt.date(), evt.start);
	mToBeAdded.push_back(std::move(nevt));
	return mToBeAdded.back().handle;
}

void EventsEditor::remove(EventHandle handle)
{
	// We don't bother to check if we actually have the event just store the handle for later
	mToBeDeleted.push_back(handle);
}

void EventsEditor::remove(Events::const_iterator start, Events::const_iterator end)
{
	auto newsize = std::distance(start, end) + mToBeDeleted.size();
	mToBeDeleted.reserve(newsize);
	std::transform(start, end, std::back_inserter(mToBeDeleted), [](const auto & value) {
		return value.handle;
	});
}

void EventsEditor::remove_day(date::year_month_day day)
{
	auto day_it_start = mEvents.begin_date(day);
	auto day_it_end = mEvents.end_date(day);
	remove(day_it_start, day_it_end);
}

void EventsEditor::remove_period(date::year_month_day start, date::year_month_day end)
{
	auto day_it_start = mEvents.begin_date(start);
	auto day_it_end = mEvents.end_date(end);
	remove(day_it_start, day_it_end);
}

void EventsEditor::clear()
{
	mClearAll = true;
}

void EventsEditor::change(EventHandle oldEvent, const Resource * resource)
{
	mToBeChangedResource.emplace_back(oldEvent, resource);
}

void EventsEditor::change(EventHandle oldEvent, model::property::Map pmap)
{
	mToBeChangedProperties.emplace_back(oldEvent, std::move(pmap));
}

void EventsEditor::change(EventHandle oldEvent, const Resource * resource, model::property::Map pmap)
{
	change(oldEvent, resource);
	change(oldEvent, std::move(pmap));
}

EventHandle EventsEditor::move_impl(const Event * mPrior, date::year_month_day day, model::time::HourMinute starttime, model::time::Duration length) {
	EventHandle nHandle;

	if (!mPrior)
		return NullHandle;

	if (mPrior->properties) {
		nHandle = create(day, starttime, length, mPrior->value, mPrior->properties);
	}
	else {
		nHandle = create(day, starttime, length, mPrior->value);
	}

	remove(mPrior->handle);
	return nHandle;
}



EventHandle EventsEditor::move(EventHandle oldEvent, date::year_month_day day, model::time::HourMinute starttime, model::time::Duration length)
{
	auto oldevt = mEvents.find(oldEvent);
	return move_impl(oldevt, day, starttime, length);

}

EventHandle EventsEditor::move(EventHandle oldEvent, date::year_month_day day)
{
	auto oldevt = mEvents.find(oldEvent);
	if (!oldevt)
		return NullHandle;
	return move_impl(oldevt, day, oldevt->start, oldevt->minutes);
}

EventHandle EventsEditor::move(EventHandle oldEvent, model::time::HourMinute starttime, model::time::Duration length)
{
	auto oldevt = mEvents.find(oldEvent);
	if (!oldevt)
		return NullHandle;
	return move_impl(oldevt, oldevt->handle, starttime, length);
}


void EventsEditor::changes_commit()
{
	// The order of operations is very important. 
	// First do the change operations (as they require reads from the data)
	// Second do the remove operations (no reads required)
	// Third do the creation operations (no reads required)
	// Then re-sort the data
	mEvents.lock_write();
	// Change block
	apply_value(mEvents, mToBeChangedResource);
	apply_value(mEvents, mToBeChangedProperties);

	// Remove Block
	if (mClearAll) {
		apply_clear(mEvents);
	}
	else {
		std::sort(mToBeDeleted.begin(), mToBeDeleted.end());
		apply_remove(mEvents, mToBeDeleted);
	}
	
	// Creation block
	apply_create(mEvents, std::move(mToBeAdded));
	
	mClearAll = false;

	mEvents.unlock_write(true);
}


EventsEditor::ChangeHistory EventsEditor::changes_make_history()
{
	// The order of operations is very important. 
	// First do the change operations (as they require reads from the data)
	// Second do the remove operations (no reads required)
	// Third do the creation operations (no reads required)
	// Then re-sort the data
	mEvents.lock_read();
	Events events{ mEvents };
	mEvents.unlock_read();

	// Change block
	apply_value(events, mToBeChangedResource);
	apply_value(events, mToBeChangedProperties);

	// Remove Block
	if (mClearAll) {
		apply_clear(events);
	}
	else {
		std::sort(mToBeDeleted.begin(), mToBeDeleted.end());
		apply_remove(events, mToBeDeleted);
	}

	// Creation block
	apply_create(events, mToBeAdded);

	bool tempClear = mClearAll;

	mClearAll = false;

	events.sort();

	return { std::move(events),std::move(EventDiff{
		tempClear,
		std::move(mToBeDeleted),
		std::move(mToBeAdded),
		std::move(mToBeChangedResource),
		std::move(mToBeChangedProperties)}) };
}

void EventsEditor::changes_discard()
{
	mToBeAdded.clear();
	mToBeChangedProperties.clear();
	mToBeDeleted.clear();
	mToBeChangedResource.clear();
	mClearAll = false;
	mExistingHandles.clear();
}

void EventsEditor::apply_value(Events & events, const std::vector<std::pair<EventHandle, const model::resource::Value *>> & from) {
	for (auto & it : from) {
		auto evt = events.find(it.first);
		if (evt) {
			evt->value = it.second;
		}
	}
}
void EventsEditor::apply_value(Events & events, const std::vector<std::pair<EventHandle, model::property::Map >> & from) {
	for (auto & it : from) {
		auto evt = events.find(it.first);
		if (evt) {
			evt->properties = std::make_shared<model::property::Map>(it.second);
		}
	}
}

void EventsEditor::apply_clear(Events & events) {
	events.get().clear();
}

void EventsEditor::apply_remove(Events & events, const std::vector<EventHandle> & from) {
	assert((std::is_sorted(from.begin(), from.end())));
	auto itRemover = from.begin();
	auto itEnd = from.end();

	auto eraser = std::remove_if(events.begin(), events.end(), [&itRemover, &itEnd](auto & x) -> bool {
		while ((itRemover != itEnd) && (*itRemover < x)) ++itRemover;
		return (itRemover != itEnd) && (*itRemover == x);
	});

	events.get().erase(eraser, events.end());
}

void EventsEditor::apply_create(Events & events, const std::vector<Event> & from) {
	std::copy(from.begin(), from.end(), std::back_inserter(events.get()));
}
void EventsEditor::apply_create(Events & events, std::vector<Event> && from) {
	std::move(from.begin(), from.end(), std::back_inserter(events.get()));
}