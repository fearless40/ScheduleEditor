#pragma once

#include <vector>
#include <array>
#include <list>

#include "TimeDuration.h"
#include "Model.h"
#include "Resources.h"


namespace Model::Data {
	
	/// Holds a group of Ranges. Allowing discontinous data to be stored
	/// It is associated with only one type of resource (the mResource)
	/// Only one DataResource per Resource! 
	class DataResource {
		// Index for loading and saving
		Index mIndex;

		// The owning resource
		const Model::Resources::Resource * mResource;
		
		// Holds the range of dates that the datastore has data for. It just has the first date and the last date.
		// Makes it more efficent for querys to the datastore not to request data that does not exist.
		// may get pushed off into the datastore api but placed in here for now
		Time::DateRange mDBInfo;

		// Class will take the events and process them into Years, months, days. This acts as a small form of compression
		// also will help make access to certain queries much faster and easier
	
		struct Event {
			Model::Resources::Resource * value;
			unsigned char hour;
			unsigned char minute;
			uint16_t duration_minutes;
		};

		struct DayIndex {
			unsigned char day;
			std::vector<Event> events;
		};

		struct MonthIndex {
			unsigned char month;
			std::vector<DayIndex> days;
		};

		struct YearIndex {
			uint16_t year;
			std::array<MonthIndex, 12> months;
		};
				
		std::list<YearIndex> mYears;
	public:
		const RangeView get_dates(date::year_month_day start, date::year_month_day end);
		const RangeView get_month(int year, int month);
		

		void		refresh();
		
		const Model::Resources::Resource & owner() const;
		const Model::Slots::SlotGroup & slots() const;

		bool isDefaultModel() const;

		/// Checks to see if the given resource has a DataModel associated with it
		static bool			HasData(const Model::Resources::Resource & res);
		
		/// Throws if it can't find the data, returns the default data model
		static DataModel &	GetDefaultModel(const Model::Resources::Resource & res);

		/// Returns a list of all the data models that a resource has associated with it
		static std::vector<DataModel &> GetAllModels(const Model::Resources::Resource & res);

		/// Throws if the data already exists
		static DataModel &	Create(const Model::Resources::Resource & res, const Model::Resources::ResourceGroup & allowedEntries, const Slots::SlotGroup & slots);

		/// Triggers an event changed signal
		static void			Save(const Model::Data::Range & changed);

	};
}