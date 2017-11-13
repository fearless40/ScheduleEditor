#include <variant>
#include <memory>
#include <vector>

#include "Event.h"
#include "Events.h"
#include "property\Map.h"

namespace model::event {
	
	class EventDiff {
		using Prior = std::variant< std::unique_ptr<EventDiff>, std::unique_ptr<model::event::Events> >;

		Prior mPrior;
		bool mCleared;
		std::vector<EventHandle> mToBeDeleted;
		std::vector<Event>		 mToBeAdded;
		std::vector<std::pair<EventHandle, const model::resource::Value *> >	mToBeChangedResource;
		std::vector<std::pair<EventHandle, model::property::Map > >		mToBeChangedProperties;

		const Events & inflate(const Prior & prior) const;
	public:

		struct Summary {
			bool ClearAll{ false };
			int Removed{ 0 };
			int Added{ 0 };
			int ValueChanged{ 0 };
			int PropertiesChanged{ 0 };
		};

		using NonOwnerPrior = std::variant< EventDiff *, Events *>;

		const Events & inflate() const;

		void prior_set(std::unique_ptr<EventDiff> diff) {
			mPrior = std::move(diff);
		}
		void prior_set(std::unique_ptr<model::event::Events> events) {
			mPrior = std::move(events);
		}

		const Summary summary() const noexcept {
			return { mCleared, mToBeDeleted.size(), mToBeAdded.size(), mToBeChangedResource.size(), mToBeChangedProperties.size() };
		}

		NonOwnerPrior prior_get() const noexcept;

		EventDiff(bool clear, std::vector<EventHandle> && mtbd, std::vector<Event> && mtba,
			std::vector<std::pair<EventHandle, const model::resource::Value *>> && mtbcr,
			std::vector<std::pair<EventHandle, model::property::Map >> && mtbcp) :
			mCleared(clear),
			mToBeDeleted(mtbd),
			mToBeAdded(mtba),
			mToBeChangedResource(mtbcr),
			mToBeChangedProperties(mtbcp) {};
	

	};


}