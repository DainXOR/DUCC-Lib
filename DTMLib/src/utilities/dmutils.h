#pragma once

#include <array>

namespace duc::math_utils {

	template <typename size_type, size_t size>
	constexpr std::array<size_type, size>
		calculateMultipliers(const auto& values) noexcept {

		std::array<size_type, size> multipliersArray{};
		
		multipliersArray[size - 1] = 1;

		for (size_t i = size - 1; i > 0; i--) {
			multipliersArray[i - 1] = multipliersArray[i] * values[i];
		}

		return multipliersArray;
	}

}