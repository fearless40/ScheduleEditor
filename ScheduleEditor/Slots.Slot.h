#pragma once

namespace Model::Slots {
	struct Slot {
	Properties::PropertyMap mProperty;
	Model::Time::HourMinute start;
	Model::Time::Duration duration;
	//const SlotGroup * const mOwner;

	private:
	uint32_t	mSlotOrder;
	};
}
