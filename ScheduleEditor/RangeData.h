#pragma once

#include "Range.h"

namespace Model::Data::Range {

	/// All resources are organized by days and then by slots. 
	/// A range is always continous set of dates. Empty spots are represented by nullptr
	/// <remarks> Ranges can only be merged if they would produce a 
	/// contigous day range. </remark>

	class Data {
		
	public:
		const Model::Data::DataModel & model() const;

		bool empty() const;

		class iterator_day {};
		class iterator_slot {};

		Date date_start() const;
		Date date_end() const;

		iterator_day begin();
		iterator_day end();

		iterator_day operator[] (Date dt);
		iterator_day operator[] (uint32_t offset);

		const iterator_day begin() const;
		const iterator_day end() const;

		const iterator_day operator[] (Date dt) const;
		const iterator_day operator[] (uint32_t offset) const;

		iterator_day at(Date dt);
		iterator_day at(uint32_t offset);

		const iterator_day at(Date dt) const;
		const iterator_day at(uint32_t offset) const;

		Model::Data::Range::View	 at(Date start, Date end) const;
		Model::Data::Range::View	 view_get(Date start, Date end) const;
		
		const iterator_slot slots(Date dt) const;
		const iterator_slot slots(uint32_t offset) const;

		const iterator_slot begin_slots() const;
		const iterator_slot end_slots() const;

		iterator_slot slots(Date dt);
		iterator_slot slots(uint32_t offset);

		iterator_slot begin_slots();
		iterator_slot end_slots();
	};
}