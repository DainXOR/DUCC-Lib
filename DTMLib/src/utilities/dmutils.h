#pragma once

#include <array>

namespace duc::math_utils {
	namespace helper {

		template <typename size_type, std::size_t Size>
		[[nodiscard]] constexpr std::array<size_type, Size>
			getMultipliers(const std::array<size_type, Size>& values) noexcept {

			std::array<size_type, Size> multipliersArray{};

			multipliersArray[Size - 1] = 1;
			((multipliersArray[Size - i - 2] = multipliersArray[Size - i - 1] * values[Size - i - 1]), ...);

			return multipliersArray;
		}



	}
}