#include "pch.h"
#include <sstream>
#include "model.h"
#include "Property.h"

using namespace model::property;

namespace model::property {
	model::string PropertyAsString(const Property & prop)
	{
		return std::visit([](auto && x) -> model::string {
			using T = std::decay_t<decltype(x)>;
			if constexpr (std::is_same_v<T, model::string>) {
				return x;
			}
			else {
				std::basic_ostringstream<model::string::value_type> ss;
				ss << x;
				return ss.str();
			}

		}, prop);
	}
}
