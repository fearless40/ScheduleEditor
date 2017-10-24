#include "pch.h"
#include <sstream>
#include <variant>
#include "Resources.Resource.h"

std::wstring Model::Resources::Resource::get() const noexcept
{
	return std::visit([](auto && x) -> std::wstring {
		using T = std::decay_t<decltype(x)>;
		if constexpr (std::is_same_v<T, std::wstring>) {
			return x;
		}
		else {
			std::wostringstream ss;
			ss << x;
			return ss.str();
		}

	}, mValue);
}
