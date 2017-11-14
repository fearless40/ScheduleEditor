#include "pch.h"
#include "Events.h"
#include "EventDiff.h"
#include "EventsEditor.h"

using namespace model::event;

const Events EventDiff::inflate(Events start, std::vector<EventDiff>::const_iterator hxBegin, std::vector<EventDiff>::const_iterator hxEnd)
{
	for (auto it = hxBegin; it != hxEnd; ++it) {
		if (it->mCleared) {
			EventsEditor::apply_clear(start);
		} 
		else {
			EventsEditor::apply_value(start, it->mToBeChangedResource);
			EventsEditor::apply_value(start, it->mToBeChangedProperties);
			EventsEditor::apply_remove(start, it->mToBeDeleted);
		}
		EventsEditor::apply_create(start,it->mToBeAdded);
	}

	return start;
}
