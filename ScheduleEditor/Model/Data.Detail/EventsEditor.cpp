#include "../../pch.h"
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

EventHandle Model::Data::Detail::EventsEditor::create(date::year_month_day day, Model::Time::HourMinute starttime, Model::Time::Duration length, Resource * resource)
{
	return EventHandle();
}

EventHandle Model::Data::Detail::EventsEditor::create(date::year_month_day day, Model::Time::HourMinute starttime, Model::Time::Duration length, Resource * resource, Model::Properties::PropertyMapUniquePtr pmap)
{
	return EventHandle();
}

EventHandle Model::Data::Detail::EventsEditor::create(const Model::Data::Event & evt)
{
	return EventHandle();
}

void Model::Data::Detail::EventsEditor::remove(EventHandle handle)
{
}

void Model::Data::Detail::EventsEditor::remove(Events::const_iterator start, Events::const_iterator end)
{
}

void Model::Data::Detail::EventsEditor::remove_day(date::year_month_day day)
{
}

void Model::Data::Detail::EventsEditor::remove_period(date::year_month_day start, date::year_month_day end)
{
}

void Model::Data::Detail::EventsEditor::clear()
{
}

void Model::Data::Detail::EventsEditor::change(EventHandle oldEvent, Resource * resource)
{
}

void Model::Data::Detail::EventsEditor::change(EventHandle oldEvent, const Model::Properties::PropertyMap pmap)
{
}

void Model::Data::Detail::EventsEditor::change(EventHandle oldEvent, Resource * resource, const Model::Properties::PropertyMap pmap)
{
}

EventHandle Model::Data::Detail::EventsEditor::move(EventHandle oldEvent, date::year_month_day day, Model::Time::HourMinute starttime, Model::Time::Duration length)
{
	return EventHandle();
}

EventHandle Model::Data::Detail::EventsEditor::move(EventHandle oldEvent, date::year_month_day day)
{
	return EventHandle();
}

EventHandle Model::Data::Detail::EventsEditor::move(EventHandle oldEvent, Model::Time::HourMinute starttime, Model::Time::Duration length)
{
	return EventHandle();
}

bool Model::Data::Detail::EventsEditor::commit_changes_only_memory()
{
	return false;
}
