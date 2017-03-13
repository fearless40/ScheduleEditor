#pragma once

#include "date\date.h"

class Model::Slots::Slot;
class Model::Slots::SlotGroup<Slot>;
class Model::Resources::Resource;
class Model::Resources::ResourceGroup;

namespace Model::Data {

	

	class RangeData {
		date startdate;
		date enddate;
		
		std::vector<uint8_t> mData;
		std::vector<const Resource *> mMapper;

		Range(const Range & r, startdate, enddate) { return copy_if(startdate, enddate matches); }
	};

	class RangeView {
		date startdate;
		date enddate;
		const RangeData & mRange;

		RangeData edit(startdate,enddate) {
			return RangeData(mRange, startdate, enddate);
		}
	};

	class iterator_slot {
		long slotindex;

	};

	// Iterates over each day in the range
	class iterator_day {



		const Resource & operator[] (long slotindex) const;
		const Resource & operator[] (const Slot & slot) const;

		const Resource & operator[] (long slotindex);
		const Resource & operator[] (const Slot & slot);


	};
	
	
	class Range {
	public:

		
		
		

		virtual bool empty() const;
		virtual bool dirty() const;

		virtual Model::Data::DataModel & model() const;

		//virtual const Resource * at(date::year_month_day dt, uint32_t slotid) const;
		virtual const IRange * at(date::year_month_day dt) const;
		virtual const IRange * at(date::year_month_day start, date::year_month_day end) const;

		virtual iterator_day begin();
		virtual iterator_day end();

		/// Returns the old value
		virtual Model::Resources::Resource * change(date::year_month_day day, long SlotIndex, Model::Resources::Resource * value);

		/// Change multiple days but only a single slot within those days
		/// <example> You wanted to clear out from 5/5 to 5/10 only the 6th slot </example>
		virtual void change(date::year_month_day start, date::year_month_day end, long SlotIndex, Model::Resources::Resource * value);

		/// Overwrite each day with the slot
		virtual void change(date::year_month_day start, date::year_month_day end, Model::Resources::Resource * value);
	};

	/// All resources are organized by days and then by slots. 
	/// A range is always continous set of dates. Empty spots are represented by nullptr
	/// <remarks> Ranges can only be merged if they would produce a 
	/// contigous day range. </remark>
	class Range
	{
		using ResourcesVector = std::vector<const Model::Resources::Resource *>;

		// Time is stored in 1 day increments
		date::year_month_day mStart;
		date::year_month_day mEnd;

	
		// Resource that this range is associated with
		const Model::DataModel & mOwner;

		// Actual data
		ResourcesVector mResources;

	public:
		/*class iterator_day : public std::iterator<
			std::random_access_iterator_tag,
			Resources::iterator>
			
		{
			long mAdvanceby{ 0 };
			Resources::iterator mIt;

		public:
			explicit iterator_day(long advanceby, Resources::iterator it) : mAdvanceby(advanceby), mIt(it) {}
			iterator_day & operator++() { mIt += mAdvanceby; return *this; }
			iterator_day operator++(int) {
				iterator_day ret(mAdvanceby, mIt);
				return (++ret);
			}
			bool operator == (iterator_day other) const { return (mIt == other.mIt); }
			bool operator != (iterator_day other) const { return (mIt != other.mIt); }
			reference operator*() const { return mIt; }
		};*/
			
			

		Range();
		~Range();

		Range(Range &&) = default;
		Range(const Range &) = default;

		/// If it is an empty range. 
		bool empty () const;

		// Get a copy limiting the selection to what is asked
		Range get(date::year_month_day day) const;
		Range get(date::year_month_day start, date::year_month_day end) const;


		// Allows the data to be edited. Copies the current object
		Range edit() const;
		Range edit(date::year_month_day day) const;
		Range edit(date::year_month_day start, date::year_month_day end) const;
		
		//const Range merge(const Range & other);

		/// Change a single slot
		void change(date::year_month_day day, long SlotIndex, Model::Resources::Resource * value);
		
		/// Change multiple days but only a single slot within those days
		/// <example> You wanted to clear out from 5/5 to 5/10 only the 6th slot </example>
		void change(date::year_month_day start, date::year_month_day end, long SlotIndex, Model::Resources::Resource * value);
		
		/// Overwrite each day with the slot
		void change(date::year_month_day start, date::year_month_day end,  Model::Resources::Resource * value);

		/// Same as change(start,end, nullptr)
		void clear(date::year_month_day start, date::year_month_day end);
		
	//	friend class RangeView;
	};

	/*class RangeView
	{
		Range * mView;
		Range::Resources::const_iterator mBegin;
		Range::Resources::const_iterator mEnd;
	};*/

}