#pragma once



namespace Model {
	
	/// Holds a group of Ranges. Allowing discontinous data to be stored
	/// It is associated with only one type of resource (the mOwner)
	class DataModel {
		Index mIndex;

		// The owning resource
		const Model::Resources::Resource * mOwner;
		
		// The resource group which defines which resources types are allowed to be stored in this data model
		const Model::Resources::ResourceGroup * mMembers;

		// The way the data is organized in the model
		const Model::Slots::SlotGroup * mSlots;

		
		// Prob use a boost::multi index to get this to work properly
		//boost::multiindex<blah blah blah> ranges;

	public:
		const RangeView get_dates(date::year_month_day start, date::year_month_day end);
		const RangeView get_month(int year, int month);
		

		void		refresh();
		
		const Model::Resources::Resource & owner() const;
		const Model::Slots::SlotGroup & slots() const;

		bool isDefaultModel() const;

		/// Checks to see if the given resource has a DataModel associated with it
		static bool			HasData(const Model::Resources::Resource * res);
		
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