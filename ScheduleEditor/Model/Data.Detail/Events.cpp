#include "pch.h"
#include <memory>
#include "../Resources.Resource.h"
#include "../Properties.PropertyMap.h"
#include "Event.h"
#include "Events.h"
#include "Years.h"
#include "Year.h"
#include "Month.h"
#include "Day.h"
#include "../Data.Event.h"
#include "../Data.DataStore.h"

using namespace Model::Data::Detail;

Model::Data::Detail::Events::Events(Data::DataStore & owner) : mOwner(owner)
{
	//mYears = std::make_unique<Years*>();

}

Model::Data::Detail::Events::~Events()
{
}

// Helper functions
template <typename SearchWho, typename SearchType>
auto add_event(const SearchWho * owner, SearchType s) -> decltype(owner->find(s)) {
	auto ret = owner->find(s);
	if (ret) {
		return ret;
	}
	else {
		auto ed = owner->edit();
		return ed.add(s);
	}
}

EventHandle Model::Data::Detail::Events::add(Model::Data::Event evt)
{
	Event iEvent;
	//iEvent.handle = make_handle(evt.mDate);
	auto date = evt.mDate;
	auto year = add_event<Years, date::year>(mYears.get(), date.year);
	auto month = add_event<Month, date::month>(year, date.month);
	auto day = add_event<Day, date::day>(days, date.day);
	
}
