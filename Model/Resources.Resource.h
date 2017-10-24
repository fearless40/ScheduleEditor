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
		
		Properties::Property mValue;
		
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
		
		/// Cannot create a resource without an owner or an id
		Resource() = delete;

		/// Checks to see if the resouce has been deleted. Deleted resource are still kept around unless all references to them have been removed
		/// <remarks> Resource are not deleted right away as parts of the schedule will still rely on them. The data will still
		/// exist in the file however it will no longer be editable. The resource will not be selected for new data entry. </remarks>
		bool isDeleted() const noexcept { return mIsDeleted; }
		
		/// ID is used only internally as there is no way to identify unique resource without looking at 
		/// mMap and scanning it for its values
		ResourceID id() const noexcept { return mId; }
		
		void markAsDeleted() noexcept { mIsDeleted = true; }

		const ResourceType & resource_type() const noexcept { return mType; }

		template <typename type> 
		type get_typed_value() const noexcept {
			return std::get<type>(mValue);
		}
		
		template <typename T> 
		void set(T value) noexcept {
			mValue = value;
		}

		std::wstring get() const noexcept;
	};

}