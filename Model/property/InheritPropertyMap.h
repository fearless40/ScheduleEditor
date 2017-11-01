#pragma once

#include "Map.h"

namespace model::property {
	class PropertyMap;

	/// Helper class to allow composition of objects to save typing.
	class InheritPropertyMap {
		Map mProperties;

	public:
		Map & properties() { return mProperties;  }
		const Map & properties() const { return mProperties; }
	};
}