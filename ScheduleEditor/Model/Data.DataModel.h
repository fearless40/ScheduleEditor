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
	class DataModel {
		// Index for loading and saving
		Index mIndex;

		// The owning resource
		const Model::Resources::Resource * mResource;
		
		// Holds the range of dates that the datastore has data for. It just has the first date and the last date.
		// Makes it more efficent for querys to the datastore not to request data that does not exist.
		// may get pushed off into the datastore api but placed in here for now
		Time::DateRange mDBInfo;

		// Is default resource model for the resource
		bool mDefault;

	public:
		const Range get_dates(date::year_month_day start, date::year_month_day end);
		const Range get_month(int year, int month);
	
		void		refresh();
		
		const Model::Resources::Resource & owner() const;

		bool isDefaultModel() const;

		/// Checks to see if the given resource has a DataModel associated with it
		static bool			HasData(const Model::Resources::Resource & res);
		
		/// Throws if it can't find the data, returns the default data model
		static DataModel &	GetDefaultModel(const Model::Resources::Resource & res);

		/// Returns a list of all the data models that a resource has associated with it
		static std::vector<DataModel &> GetAllModels(const Model::Resources::Resource & res);

		/// Throws if the data already exists
		static DataModel &	Create(const Model::Resources::Resource & res, const Model::Resources::ResourceGroup & allowedEntries);

		/// Triggers an event changed signal
		static void			Save(const Model::Data::Range & changed);

	};
}