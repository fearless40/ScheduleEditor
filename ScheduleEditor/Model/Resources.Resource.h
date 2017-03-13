#pragma once

#include "Resources.h"

namespace Model::Resources {
	
	/// Holds the data for each event/person/place. Flexible and owned by ResourceType
	class Resource
	{
		Properties::PropertyMap mProperties;
		const ResourceType & mType;

	public:
		

		const Model::Properties::PropertyMap & properties_get();

		// Helpful to allow if() like constructs to check if something is empty or null
		operator bool() { return (this != &NullResource); }


	};

	static Resource NullResource;
}