#pragma once

namespace Model::Slots {

	using namespace Model;

	class Slot 
	{
	Properties::PropertyMap mProperty;
	Model::Time::HourMinute start;
	Model::Time::Duration duration;
	//const SlotGroup * const mOwner;
	public:
		const Properties::PropertyMap & properties_get();

		template<class DurationType>
		void duration_set(DurationType t) {
			duration = t;
		}

		Time::HourMinute start_get() const;

		void start_set(Time::HourMinute tm);

	private:
	uint32_t	mSlotOrder;
	};
}
