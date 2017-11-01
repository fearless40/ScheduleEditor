#pragma once

#include "../../Lib/boost/boost/iterator/transform_iterator.hpp"
#include "Data.Detail\Event.h"
#include "Data.Detail\Events.h"
#include "Data.Event.h"
#include "Data.Datamodel.h"

namespace model {

	
	/// A view into a Data. Lightweight class pass by value. 
	/// Always const cannot edit data.
	class Range {
		model::Data::Detail::EventHandle mStart{ 0 };
		model::Data::Detail::EventHandle mEnd{ 0 };
		const model::Data::Detail::Events & mEvents;
		const model::Data::Datamodel & mmodel;
		
		struct TransFormer {
			const model::Data::Event operator ()(model::Data::Detail::Events::const_iterator &it) {
				return *it;
			}
		};

	public:

		using const_iterator = boost::transform_iterator<TransFormer, model::Data::Detail::Events::const_iterator>;

		const model::Data::Datamodel & model() const noexcept { return mmodel; }

		bool empty() const noexcept { return mStart.value == 0 || mEnd.value == 0; }

		date::year_month_day date_start() const noexcept;
		date::year_month_day date_end() const noexcept;

		std::size_t count() const;

		const_iterator begin() const {
			return boost::make_transform_iterator(mEvents.find_iterator(mStart), TransFormer{});
		}
		const_iterator end() const {
			return boost::make_transform_iterator(mEvents.find_iterator(mEnd), TransFormer{});
		}

		Range subset(date::year_month_day start, date::year_month_day end) const;


	};
}