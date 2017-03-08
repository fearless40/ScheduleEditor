#pragma once

class Model::Slots::Slot;
class Model::Slots::SlotGroup<Slot>;
class Model::Resources::Resource;
class Model::Resources::Group;

namespace Model::Data {

	class RangeView;

	/// All resources are organized by days and then by slots. 
	/// A range is always continous set of dates. Empty spots are represented by nullptr
	/// <remarks> Ranges can only be merged if they would produce a 
	/// contigous day range. </remark>
	class Range
	{
		using Resources = std::vector<const Resource *>;

		// Time is stored in 1 day increments
		date::year_month_day mStart;
		date::year_month_day mEnd;

		// Slot group
		const Model::Slots::SlotGroup<Slot> * mSlots;

		// Resource Group allowed
		const Model::Resources::Group * mResourceGroup;

		// Actual data
		Resources mResources; 

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

		/// If it is an empty range. It can exist if you try to merge to non contigous ranges
		bool empty () const;

		const Range get(date::year_month_day day) const;
		const Range get(date::year_month_day start, date::year_month_day end) const;

		// Allows the data to be edited
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