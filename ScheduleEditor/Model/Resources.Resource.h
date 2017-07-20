#pragma once

#include "Resources.h"
#include "Properties.PropertyMap.h"

namespace Model::Resources {
	
	/// Holds the data for each event/person/place. Flexible and owned by ResourceType
	class Resource : public Properties::PropertyMap
	{
		const ResourceType & mType;
		bool mIsDeleted{ false };
		ResourceID mId{ 0 };
		
	public:

		Resource(const ResourceType & owner, ResourceID id) :
			mType(owner), mId(id) {}
		Resource(const Resource & resource) :
			mType(resource.mType), mIsDeleted(resource.mIsDeleted), mId(resource.mId) {
			mMap.insert(resource.begin(), resource.end());
		}
		Resource(const ResourceType & owner, ResourceID id, const Properties::PropertyMap & map) :
			mType(owner), mId(id) {
			mMap.insert(map.begin(), map.end());
		}
		Resource(const ResourceType & owner, ResourceID id, bool isDeleted, const Properties::PropertyMap & map) :
			mType(owner), mId(id),  mIsDeleted(isDeleted) {
			mMap.insert(map.begin(), map.end());
		}
		Resource(const ResourceType & owner, ResourceID id, bool isDeleted) :
			mType(owner), mId(id) , mIsDeleted(isDeleted) {
		}


		Resource(Resource &&) = default;
		Resource() = delete;

		/// Checks to see if the resouce has been deleted. Deleted resource are still kept around unless all references to them have been removed
		/// <remarks> Resource are not deleted right away as parts of the schedule will still rely on them. The data will still
		/// exist in the file however it will no longer be editable. The resource will not be selected for new data entry. </remarks>
		bool isDeleted() const { return mIsDeleted; }
		ResourceID getId() const{ return mId; }
		
		void markAsDeleted() { mIsDeleted = true; }

		const ResourceType & getType() const { return mType; }

		
	};

//	static Resource NullResource;
}