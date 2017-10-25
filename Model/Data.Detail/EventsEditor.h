#pragma once


#include "Event.h"
#include "Events.h"
#include <unordered_set>

class Model::Data::Event;
class Model::Resources::Resource;
class Model::Data::Detail::Events;

namespace Model::Data::Detail {

	class EventsEditor {
		std::vector<EventHandle> mToBeDeleted;
		std::vector<Event>		 mToBeAdded;
		
		std::vector<std::pair<EventHandle, Model::Resources::Resource *> >		 mToBeChangedResource;
		std::vector<std::pair<EventHandle, Model::Properties::PropertyMapUniquePtr> >		 mToBeChangedProperties;
		
		std::unordered_set<EventHandle> mExistingHandles;
		
		Events & mEvents;

		bool mClearAll{ false };

		EventHandle new_handle(date::year_month_day day, Model::Time::HourMinute starttime);
		EventHandle move_impl(const Event * mPrior, date::year_month_day day, Model::Time::HourMinute starttime, Model::Time::Duration length);


	public:


		EventsEditor(Events & evt);
		~EventsEditor();

		// Moveable
		EventsEditor(EventsEditor && evt) = default;

		// Non copyable
		EventsEditor(const EventsEditor & evt) = delete;
		EventsEditor operator = (const EventsEditor & evt) = delete;

		EventHandle create(date::year_month_day day, Model::Time::HourMinute starttime, Model::Time::Duration length, Model::Resources::Resource * resource);
		EventHandle create(date::year_month_day day, Model::Time::HourMinute starttime, Model::Time::Duration length, Model::Resources::Resource * resource, Model::Properties::PropertyMapUniquePtr pmap);
		EventHandle create(const Model::Data::Event & evt);
		
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

		void change(EventHandle oldEvent, Model::Resources::Resource * resource);
		void change(EventHandle oldEvent, const Model::Properties::PropertyMap & pmap);
		void change(EventHandle oldEvent, Model::Resources::Resource * resource, const Model::Properties::PropertyMap & pmap);
		
		EventHandle move(EventHandle oldEvent, date::year_month_day day, Model::Time::HourMinute starttime, Model::Time::Duration length);
		EventHandle move(EventHandle oldEvent, date::year_month_day day);
		EventHandle move(EventHandle oldEvent, Model::Time::HourMinute starttime, Model::Time::Duration length);

		void commit_changes_only_memory();
		//bool commit_changes_to_filesystem();
	};

}