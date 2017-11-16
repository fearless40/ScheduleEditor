#pragma once

#include <variant>
#include <memory>
#include <vector>

#include "Event.h"
#include "Events.h"
#include "..\property\Map.h"

namespace model::event {
	
	class EventDiff {
		bool mCleared;
		std::vector<EventHandle> mToBeDeleted;
		std::vector<Event>		 mToBeAdded;
		std::vector<std::pair<EventHandle, const model::resource::Value *> >	mToBeChangedResource;
		std::vector<std::pair<EventHandle, model::property::Map > >		mToBeChangedProperties;

	public:

		struct Summary {
			bool ClearAll{ false };
			std::size_t Removed{ 0 };
			std::size_t Added{ 0 };
			std::size_t ValueChanged{ 0 };
			std::size_t PropertiesChanged{ 0 };
		};

	
		const Summary summary() const noexcept {
			return { mCleared, mToBeDeleted.size(), mToBeAdded.size(), mToBeChangedResource.size(), mToBeChangedProperties.size() };
		}

		EventDiff(bool clear, std::vector<EventHandle> && mtbd, std::vector<Event> && mtba,
			std::vector<std::pair<EventHandle, const model::resource::Value *>> && mtbcr,
			std::vector<std::pair<EventHandle, model::property::Map >> && mtbcp) :
			mCleared(clear),
			mToBeDeleted(mtbd),
			mToBeAdded(mtba),
			mToBeChangedResource(mtbcr),
			mToBeChangedProperties(mtbcp) {};
	
		static const Events inflate(Events start, std::vector<EventDiff>::const_iterator hxBegin, std::vector<EventDiff>::const_iterator hxEnd);
	};


}