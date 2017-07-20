#pragma once

namespace Model::Properties {
	class PropertyMap;

	/// Helper class to allow composition of objects to save typing.
	class HasProperties {
		PropertyMap mProperties;

	public:
		PropertyMap & properties() { return mProperties;  }
		const PropertyMap & properties() const { return mProperties; }
	};
}