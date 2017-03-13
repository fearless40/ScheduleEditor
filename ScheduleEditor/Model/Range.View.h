#pragma once

#include "Range.h"

namespace Model::Data::Range {

	
	/// A view into a Data. Lightweight class pass by value. 
	/// Always const cannot edit data.
	class View {

	public:

		const Model::Data::DataModel & model() const;

		bool empty() const;

		class iterator_day {};
		class iterator_slot {};

		Date date_start() const;
		Date date_end() const;

		const iterator_day begin() const;
		const iterator_day end() const;

		const iterator_day operator[] (Date dt) const;
		const iterator_day operator[] (uint32_t offset) const;

		const iterator_day at(Date dt) const;
		const iterator_day at(uint32_t offset) const;

		View		 at(Date start, Date end) const;

		const iterator_slot slots(Date dt) const;
		const iterator_slot slots(uint32_t offset) const;

		const iterator_slot begin_slots() const;
		const iterator_slot end_slots() const;

		Model::Data::Range::Data edit() const;
		Model::Data::Range::Data edit(Date start, Date end) const;

	};
}