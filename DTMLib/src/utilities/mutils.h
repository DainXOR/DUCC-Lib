#pragma once

#include <array>

namespace duc::math_utils {

	/// > Structures

	template<typename type> 
	struct pair_equal {
		type x;
		type y;
	};
	template<typename type1, typename type2>
	struct pair_any {
		type1 x;
		type2 y;
	};

	template<typename type>
	struct triplet_equal {
		type x;
		type y;
		type z;
	};
	template<typename type1, typename type2, typename type3>
	struct triplet_any {
		type1 x;
		type2 y;
		type3 z;
	};


	/// > Functions

/// \Note	This function only works with positive exponents.
///			Helper function for powers calculation.
///			Can calculate the n-th negative power if given $base as
///			`1 / $base` and $exponent as the positive n-th power.
/// \Warn	This function modify its parameters.
/// \Return Returns the $base multiply by itself $exponent times.
/// 
	constexpr double powerPositiveInteger(double base, uint64_t exponent) noexcept {
		double result = 1;

		while (exponent > 0) {
			(((exponent & 1) == 1) && (result *= base));
			//if ((exponent & 1) == 1) { result *= base; } // exp. is odd
			base *= base;
			exponent >>= 1; // y = y / 2;
		}

		return result;
	}

	template <typename size_type, size_t size>
	constexpr auto calculateMultipliers(const auto& values) noexcept {

		std::array<size_type, size> multipliersArray{};
		
		multipliersArray[size - 1] = 1;

		for (size_t i = size - 1; i > 0; i--) {
			multipliersArray[i - 1] = multipliersArray[i] * values[i];
		}

		return multipliersArray;
	}
	
	constexpr bool isTensorsShapeCompatible(const auto& rank1, const auto& shape1, const auto& shape2) noexcept {
		for (int i = 0; i < rank1; i++) {
			if (shape1[i] != shape2[i]) {
				if (shape1[i] != 1 && shape2[i] != 1) {
					// dimensions are not compatible for summation
					return false;
				}
			}
		}
		return true;
	}

	




}