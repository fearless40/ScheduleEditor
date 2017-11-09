#pragma once


#include "Event.h"
//#include "Events.h"
#include <unordered_set>
#include "../property/Map.h"


class model::resource::Value;


namespace model::event {

	class EventsEditor {
		std::vector<EventHandle> mToBeDeleted;
		std::vector<Event>		 mToBeAdded;
		
		std::vector<std::pair<EventHandle, const model::resource::Value *> >	mToBeChangedResource;
		std::vector<std::pair<EventHandle, model::property::Map > >		mToBeChangedProperties;
		
		std::unordered_set<EventHandle> mExistingHandles;
		
		Events & mEvents;

		bool mClearAll{ false };

		

		EventHandle new_handle(date::year_month_day day, model::time::HourMinute starttime);
		EventHandle move_impl(const Event * mPrior, date::year_month_day day, model::time::HourMinute starttime, model::time::Duration length);


	public:

		bool AutoCommit{ true };

		EventsEditor(Events & evt);
		~EventsEditor();

		// Moveable
		EventsEditor(EventsEditor && evt) = default;

		// Non copyable
		EventsEditor(const EventsEditor & evt) = delete;
		EventsEditor operator = (const EventsEditor & evt) = delete;

		EventHandle create(date::year_month_day day, model::time::HourMinute starttime,	model::time::Duration length, const model::resource::Value * resource);
		EventHandle create(date::year_month_day day, model::time::HourMinute starttime, model::time::Duration length, const model::resource::Value * resource, const model::property::Map & pmap);
		EventHandle create(date::year_month_day day, model::time::HourMinute starttime, model::time::Duration length, const model::resource::Value * resource, std::shared_ptr<const model::property::Map> pmap);
		EventHandle create(const Event & evt);
		
		template< typename iterator >
		void create(const iterator & start, const iterator & end) {
			mToBeAdded.reserve(std::distance(start, end));
			for (auto i = start; i != end; ++i) {
				create(*i);
			}
		};

		template< typename iterator >
		std::vector<EventHandle> create_with_handles(const iterator & start, const iterator & end) {
			std::vector<EventHandle> handles;
			auto size = std::distance(start, end);
			mToBeAdded.reserve(size);
			handles.reserve(size);
			for (auto i = start; i != end; ++i) {
				handles.push_back(create(*i));
			}

			return handles;
		};

		void		remove(EventHandle handle);
		void		remove(Events::const_iterator start, Events::const_iterator end);
		void		remove_day(date::year_month_day day);
		// End is inclusice
		void		remove_period(date::year_month_day start, date::year_month_day end);
		void		clear();

		void change(EventHandle oldEvent, const model::resource::Value * resource);
		void change(EventHandle oldEvent, model::property::Map pmap);
		void change(EventHandle oldEvent, const model::resource::Value * resource, model::property::Map pmap);
		
		EventHandle move(EventHandle oldEvent, date::year_month_day day, model::time::HourMinute starttime, model::time::Duration length);
		EventHandle move(EventHandle oldEvent, date::year_month_day day);
		EventHandle move(EventHandle oldEvent, model::time::HourMinute starttime, model::time::Duration length);

		void changes_commit();
		void changes_discard();
	};

}