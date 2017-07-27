#pragma once

#include <chrono>
#include <vector>
#include <memory>
#include "TimeDuration.h"
#include "Resources.h"
#include "Properties.PropertyMap.h"

namespace Model::Data {

	class EventIndex;
	class DataStore {
	public:
		union EventHandle {
			struct {
				uint32_t year : 12;
				uint32_t month : 4;
				uint32_t day : 5;
				uint32_t minute : 11;
			} fields;
			uint32_t value;
		};

		static constexpr EventHandle NullHandle{ 0 };

	private:
		const Model::Data::DataModel & owner;

		// The range of dates in this Store
		Time::DateRange mDates;
		
		struct Event {
			Model::Resources::Resource * value;
			Time::HourMinute;
			Time::Duration minutes;
			EventHandle handle;
			std::unique_ptr<Model::Properties::PropertyMap> properties;
		};

		
		std::unique_ptr<EventIndex> mDataIndex;
		std::vector<EventHandle> mChangedEvents;
	
	public:

		void process_raw_events(const RawEvents & revt);
		void process_raw_events_filter(const RawEvents & revt, const Model::Resources::ResourceGroup & allowed_resources);

		RawEvents get_changed_events();
		
		void event_change(EventHandle eHandle, Model::Data::Event evt);
		void event_delete(EventHandle eHandle);
		//void event_change()

		//Obtain Views
		SlotView view_slots(Time::DateRange dates, const Model::Slots::SlotGroup & group);
		LinearView view_linear(date::year_month_day start, date::year_month_day end);
	};
}