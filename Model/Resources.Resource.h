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
						
		Properties::Property & default_value() noexcept {
			return mMap[0].value;
		}

		const Properties::Property & default_value() const noexcept {
			return mMap[0].value;
		}

		static constexpr Properties::Key::value_type * default_key = "__default" ;
		static constexpr long				    default_value_value = 0;
		
	public:

		Resource(const ResourceType & owner, ResourceID id);
		Resource(const ResourceType & owner, ResourceID id, PropertyMap && pmap);
		Resource(Resource &&) = default;
		Resource() = delete; 		/// Cannot create a resource without an owner or an id

		/// Checks to see if the resouce has been deleted. Deleted resource are still kept around unless all references to them have been removed
		/// <remarks> Resource are not deleted right away as parts of the schedule will still rely on them. The data will still
		/// exist in the file however it will no longer be editable. The resource will not be selected for new data entry. </remarks>
		bool isDeleted() const noexcept { return mIsDeleted; }
		
		/// ID is used only internally as there is no way to identify unique resource without looking at 
		/// mMap and scanning it for its values
		ResourceID id() const noexcept { return mId; }
		
		void markAsDeleted() noexcept { mIsDeleted = true; }

		const ResourceType & resource_type() const noexcept { return mType; }

		bool onlyHasDefaultValue() { return mMap.size() == 1; }

		// Default value gettes. Useful for easier programming
		template <typename type> 
		type value() const noexcept {
			return std::get<type>(default_value());
		}
		
		auto & value() noexcept {
			return default_value();
		}

		std::wstring value_asString() const noexcept {
			return Properties::PropertyAsString(default_value());
		}

		
	};

}