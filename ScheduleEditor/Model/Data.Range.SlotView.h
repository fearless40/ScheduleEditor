#pragma once

#include "Slots.h"

namespace Model::Data::Range
{
	// Holds a view of the data with events forced into a slot
	class SlotView
	{
		Model::Data::DataStore & store;
		const Model::Slots::SlotGroup & group;


	};
}