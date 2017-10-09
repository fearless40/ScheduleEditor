#include "pch.h"
#include <algorithm>
#include "../Resources.Resource.h"
#include "../Data.Event.h"
#include "EventsEditor.h"

using namespace Model::Data::Detail;
using Resource = Model::Resources::Resource;

Model::Data::Detail::EventsEditor::EventsEditor(Events & evt) : mEvents(evt)
{
}

Model::Data::Detail::EventsEditor::~EventsEditor()
{
	// Do nothing for now
}

EventHandle EventsEditor::new_handle(date::year_month_day day, Model::Time::HourMinute starttime) 
{
	EventHandle handle = mEvents.make_unique_handle(day, starttime);

	while (mExistingHandles.count(handle) == 1) {
		handle.fields.minute += 1;
	}
	
	mExistingHandles.insert(handle);

	return handle;
}

EventHandle Model::Data::Detail::EventsEditor::create(date::year_month_day day, Model::Time::HourMinute starttime, Model::Time::Duration length, Resource * resource)
{
	Event evt;
	evt.handle = new_handle(day, starttime);
	evt.start = starttime;
	evt.value = resource;
	evt.minutes = length;
	
	mToBeAdded.push_back(std::move(evt));

	return mToBeAdded.back().handle;
}

EventHandle Model::Data::Detail::EventsEditor::create(date::year_month_day day, Model::Time::HourMinute starttime, Model::Time::Duration length, Resource * resource, Model::Properties::PropertyMapUniquePtr pmap)
{
	Event evt;
	evt.handle = new_handle(day, starttime);
	evt.start = starttime;
	evt.minutes = length;
	evt.value = resource;
	evt.properties = std::move(pmap);

	mToBeAdded.push_back(std::move(evt));

	return mToBeAdded.back().handle;
}

EventHandle Model::Data::Detail::EventsEditor::create(const Model::Data::Event & evt)
{
	Event nevt;
	nevt.handle = new_handle(evt.date(), evt.start_time());
	nevt.start = evt.start_time();
	nevt.value = evt.resource();
	nevt.minutes = evt.duration();
	
	if (evt.properties()) {
		Model::Properties::PropertyMapUniquePtr pmu{ new Model::Properties::PropertyMap(*evt.properties()) };
		nevt.properties = std::move(pmu);
	}

	mToBeAdded.push_back(std::move(nevt));

	return mToBeAdded.back().handle;
}

void Model::Data::Detail::EventsEditor::remove(EventHandle handle)
{
	// We don't bother to check if we actually have the event just store the handle for later
	mToBeDeleted.push_back(handle);
}

void Model::Data::Detail::EventsEditor::remove(Events::const_iterator start, Events::const_iterator end)
{
	auto newsize = std::distance(start, end) + mToBeDeleted.size();
	mToBeDeleted.reserve(newsize);
	std::transform(start, end, std::back_inserter(mToBeDeleted), [](const auto & value) {
		return value.handle;
	});
}

void Model::Data::Detail::EventsEditor::remove_day(date::year_month_day day)
{
	auto day_it_start = mEvents.begin_date(day);
	auto day_it_end = mEvents.end_date(day);
	remove(day_it_start, day_it_end);
}

void Model::Data::Detail::EventsEditor::remove_period(date::year_month_day start, date::year_month_day end)
{
	auto day_it_start = mEvents.begin_date(start);
	auto day_it_end = mEvents.end_date(end);
	remove(day_it_start, day_it_end);
}

void Model::Data::Detail::EventsEditor::clear()
{
	mClearAll = true;
}

void Model::Data::Detail::EventsEditor::change(EventHandle oldEvent, Resource * resource)
{
	mToBeChangedResource.emplace_back(oldEvent, resource);
}

void Model::Data::Detail::EventsEditor::change(EventHandle oldEvent, const Model::Properties::PropertyMap &pmap)
{
	Model::Properties::PropertyMapUniquePtr pmu{ new Model::Properties::PropertyMap(pmap) };
	mToBeChangedProperties.emplace_back(oldEvent, std::move(pmu));
}

void Model::Data::Detail::EventsEditor::change(EventHandle oldEvent, Resource * resource, const Model::Properties::PropertyMap & pmap)
{
	change(oldEvent, resource);
	change(oldEvent, pmap);
}

EventHandle Model::Data::Detail::EventsEditor::move_impl(const Event * mPrior, date::year_month_day day, Model::Time::HourMinute starttime, Model::Time::Duration length) {
	EventHandle nHandle;

	if (!mPrior)
		return NullHandle;

	if (mPrior->properties) {
		Model::Properties::PropertyMapUniquePtr pmu{ new Model::Properties::PropertyMap(*mPrior->properties.get()) };
		nHandle = create(day, starttime, length, mPrior->value, std::move(pmu));
	}
	else {
		nHandle = create(day, starttime, length, mPrior->value);
	}

	remove(mPrior->handle);
	return NullHandle;
}

EventHandle Model::Data::Detail::EventsEditor::move(EventHandle oldEvent, date::year_month_day day, Model::Time::HourMinute starttime, Model::Time::Duration length)
{
	auto oldevt = mEvents.find(oldEvent);
	return move_impl(oldevt, day, starttime, length);

}

EventHandle Model::Data::Detail::EventsEditor::move(EventHandle oldEvent, date::year_month_day day)
{
	auto oldevt = mEvents.find(oldEvent);
	if (!oldevt)
		return NullHandle;
	return move_impl(oldevt, day, oldevt->start, oldevt->minutes);
}

EventHandle Model::Data::Detail::EventsEditor::move(EventHandle oldEvent, Model::Time::HourMinute starttime, Model::Time::Duration length)
{
	auto oldevt = mEvents.find(oldEvent);
	if (!oldevt)
		return NullHandle;
	return move_impl(oldevt, oldevt->handle, starttime, length);
}

void Model::Data::Detail::EventsEditor::commit_changes_only_memory()
{
	// The order of operations is very important. 
	// First do the change operations (as they require reads from the data)
	// Second do the remove operations (no reads required)
	// Third do the creation operations (no reads required)
	// Then re-sort the data
	mEvents.lock_write();
	{ // Change block
		
		for (auto it = mToBeChangedResource.begin(), end = mToBeChangedResource.end(); it != end; ++it) {
			auto evt = mEvents.find(it->first);
			if (evt) {
				evt->value = it->second;
			}
		}

		for (auto it = mToBeChangedProperties.begin(), end = mToBeChangedProperties.end(); it != end; ++it) {
			auto evt = mEvents.find(it->first);
			if (evt) {
				evt->properties = std::move(it->second);
			}
		}
	}

	{ // Remove Block
		if (mClearAll) {
			mEvents.get().clear();
		}
		else {
			std::sort(mToBeDeleted.begin(), mToBeDeleted.end());
			auto itRemover = mToBeDeleted.begin();
			auto itEnd = mToBeDeleted.end();

			auto eraser = std::remove_if(mEvents.begin(), mEvents.end(), [&itRemover, &itEnd](auto & x) -> bool {
				while ((itRemover != itEnd) && (*itRemover < x)) ++itRemover;
				return (itRemover != itEnd) && (*itRemover == x);
			});

			mEvents.get().erase(eraser, mEvents.end());
		}
	}
	
	
	{ // Creation block
		std::move(mToBeAdded.begin(), mToBeAdded.end(), mEvents.end());
	}
	
	mClearAll = false;

	mEvents.unlock_write(true);
	
}
