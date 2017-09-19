#pragma once

#include "../../Lib/boost/boost/iterator/transform_iterator.hpp"
#include "Data.Detail\Event.h"
#include "Data.Detail\Events.h"
#include "Data.Event.h"
#include "Data.DataModel.h"

namespace Model::Data::Range {

	
	/// A view into a Data. Lightweight class pass by value. 
	/// Always const cannot edit data.
	class Range {
		Model::Data::Detail::EventHandle mStart{ 0 };
		Model::Data::Detail::EventHandle mEnd{ 0 };
		const Model::Data::Detail::Events & mEvents;
		const Model::Data::DataModel & mModel;
		
		struct TransFormer {
			const Model::Data::Event operator(Model::Data::Detail::Events::const_iterator &it) {
				return *it;
			}
		};

	public:

		using const_iterator = boost::transform_iterator<TransFormer, Model::Data::Detail::Events::const_iterator>;

		const Model::Data::DataModel & model() const noexcept { return mModel; }

		bool empty() const noexcept { return mStart.value == 0 || mEnd.value == 0; }

		date::year_month_day date_start() const noexcept;
		date::year_month_day date_end() const noexcept;

		const_iterator begin() const {
			return boost::make_transform_iterator(mEvents.find_iterator(mStart), TransFormer{});
		}
		const_iterator end() const {
			return boost::make_transform_iterator(mEvents.find_iterator(mEnd), TransFormer{});
		}

		const_iterator operator[] (Date dt) const;
		const_iterator operator[] (uint32_t offset) const;

		const_iterator at(Date dt) const;
		const_iterator at(uint32_t offset) const;

		Range subset(Date start, Date end) const;

	};
}