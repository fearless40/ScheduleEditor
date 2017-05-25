#pragma once

#include "Resources.h"
#include "Properties.PropertyMap.h"

namespace Model::Resources {
	
	/// Holds the data for each event/person/place. Flexible and owned by ResourceType
	class Resource : public Properties::PropertyMap
	{
		const ResourceType & mType;
		bool mIsDeleted;
		
		// Only writable by ResourceType
		ResourceUniqueID mUnique;

	public:
		ResourceUniqueID getID() const;

		/// Checks to see if the resouce has been deleted. Deleted resource are still kept around unless all references to them have been removed
		/// <remarks> Resource are not deleted right away as parts of the schedule will still rely on them. The data will still
		/// exist in the file however it will no longer be editable. The resource will not be selected for new data entry. </remarks>
		bool isDeleted() const { return mIsDeleted; }

		const ResourceType & getType() const { return mType; }


		// Helpful to allow if() like constructs to check if something is empty or null
		operator bool() { return (this != &NullResource); }


	};

	static Resource NullResource;
}