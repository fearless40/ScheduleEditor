#pragma once

#include "TimeDuration.h"

namespace Model::Slots {
	/// A item that represents a time-period or organizing block
	/// Slots are strongly ordered represented by mSlotOrder
	

	const SlotGroup & FindSlotGroup(std::string name);
	const SlotGroup & FindSlotGroup(Model::Index modelIndex);

	SlotGroup & CreateSlotGroup(std::string name);
	void SaveSlotGroup(SlotGroup & group);
}