#include "pch.h"
#include <sstream>
#include "Model.h"
#include "Properties.h"


Model::string Model::Properties::PropertyAsString(const Property & prop)
{
	return std::visit([](auto && x) -> Model::string {
		using T = std::decay_t<decltype(x)>;
		if constexpr (std::is_same_v<T, Model::string>) {
			return x;
		}
		else {
			std::basic_ostringstream<Model::string::value_type> ss;
			ss << x;
			return ss.str();
		}

	}, prop);
}
