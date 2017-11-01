#pragma once


#include "timeDuration.h"
#include "model.h"
#include "Resources.h"




namespace model::events {
	
	/// Holds a group of Ranges. Allowing discontinous data to be stored
	/// It is associated with only one type of resource (the mResource)
	/// Only one DataResource per Resource! 
	class ResourceEvents {
		// The owning resource
		const model::Resources::Resource * mResource;
		model::Data::Detail::Events * mEvents;


	public:
	
		model::Index getIndex();

	};
}