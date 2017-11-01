#pragma once


#include "Event.h"
#include "Events.h"
#include <unordered_set>

class model::Event;
class model::Resources::Resource;
class model::details::Events;

namespace model::details {

	class EventsEditor {
		std::vector<EventHandle> mToBeDeleted;
		std::vector<Event>		 mToBeAdded;
		
		std::vector<std::pair<EventHandle, model::Resources::Resource *> >		 mToBeChangedResource;
		std::vector<std::pair<EventHandle, model::Properties::PropertyMapUniquePtr> >		 mToBeChangedProperties;
		
		std::unordered_set<EventHandle> mExistingHandles;
		
		Events & mEvents;

		bool mClearAll{ false };

		EventHandle new_handle(date::year_month_day day, model::time::HourMinute starttime);
		EventHandle move_impl(const Event * mPrior, date::year_month_day day, model::time::HourMinute starttime, model::time::Duration length);


	public:


		EventsEditor(Events & evt);
		~EventsEditor();

		// Moveable
		EventsEditor(EventsEditor && evt) = default;

		// Non copyable
		EventsEditor(const EventsEditor & evt) = delete;
		EventsEditor operator = (const EventsEditor & evt) = delete;

		EventHandle create(date::year_month_day day, model::time::HourMinute starttime, model::time::Duration length, model::Resources::Resource * resource);
		EventHandle create(date::year_month_day day, model::time::HourMinute starttime, model::time::Duration length, model::Resources::Resource * resource, model::Properties::PropertyMapUniquePtr pmap);
		EventHandle create(const model::Event & evt);
		
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

		void change(EventHandle oldEvent, model::Resources::Resource * resource);
		void change(EventHandle oldEvent, const model::Properties::PropertyMap & pmap);
		void change(EventHandle oldEvent, model::Resources::Resource * resource, const model::Properties::PropertyMap & pmap);
		
		EventHandle move(EventHandle oldEvent, date::year_month_day day, model::time::HourMinute starttime, model::time::Duration length);
		EventHandle move(EventHandle oldEvent, date::year_month_day day);
		EventHandle move(EventHandle oldEvent, model::time::HourMinute starttime, model::time::Duration length);

		void commit_changes_only_memory();
		//bool commit_changes_to_filesystem();
	};

}