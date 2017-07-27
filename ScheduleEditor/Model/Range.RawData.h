#pragma once

#include <chrono>
#include <vector>
#include <limits>
#include "Resources.h"
#include "Properties.h"

namespace Model::Data::Range {

	

	/// Holds a list of raw events. Main data transfer class
	// Apply Views to the RawEvents to get the necessary data.

	struct RawEvent {
		// Define an empty property index
		static const std::size_t NoProperty = std::numeric_limits<std::size_t>::max();

		// Start date in minutes
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::minutes> date;

		// Duration of the event
		std::chrono::minutes duration;

		// Index into the RawEventCollection mPropertyIndex
		std::size_t property_index = NoProperty;

		// Pointer to the resource that data for the event
		Model::Resources::Resource * resource;

		bool hasProperties() const { return property_index != NoProperty; }
	};

	struct RawEvents {

		

		std::vector<RawEvent> mEvents;
		std::vector<Model::Properties::PropertyMap> mPropertyIndex;
		const Model::Resources::Resource * mResourceOwner;
	};


}