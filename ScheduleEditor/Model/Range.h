#pragma once

#include "date\date.h"

class Model::Slots::Slot;
class Model::Slots::SlotGroup<Slot>;
class Model::Resources::Resource;
class Model::Resources::ResourceGroup;
class Model::Data::DataModel;


namespace Model::Data::Range {

	
	using Date = date::year_month_day;
	class Data;
	class View;

}