#include "pch.h"
#include "event\Event.h"
#include "event\Events.h"
#include "event\EventDiff.h"
#include "event\EventsEditor.h"
#include "Schedule.h"


using namespace model;

event::EventsEditor Schedule::edit() const
{
	return mCurrent.edit();
}

void Schedule::changes_commit(event::EventsEditor && editor)
{
	auto changes = editor.changes_make_history();
	//todo: add synchronization in here
	mCurrent = std::move(changes.events);
	mHistory.push_back(std::move(changes.diff));
}

void Schedule::changes_commit_no_history(event::EventsEditor && editor)
{
}

void model::Schedule::history_clear()
{
	mBeginHistory = mCurrent;
	mHistory.clear();
}
