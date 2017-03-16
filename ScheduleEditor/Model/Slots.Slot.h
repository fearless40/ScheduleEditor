#pragma once

#include "Slots.h"

namespace Model::Slots {

	using namespace Model;

	class Slot 
	{
		Properties::PropertyMap mProperty;
		Time::HourMinute mStart;
		Time::Duration mDuration;
		
	public:
		const Properties::PropertyMap & properties() const;
		Properties::PropertyMap & properties();

		Time::HourMinute start() const;
		void start(Time::HourMinute tm);

		Model::Time::Duration duration() const;
		void duraton(Time::Duration length);


		

	private:
		uint32_t	mSlotOrder;
	};
}
