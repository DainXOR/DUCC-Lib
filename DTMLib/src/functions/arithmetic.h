#pragma once
#include <type_traits>

#include "../utilities/constrains.h"

namespace duc {

	// Complex base, integral exponent
	constexpr auto exp(const require::Complex auto& base, const require::Integral auto& exponent) {
		std::remove_const_t<std::remove_reference_t<decltype(base)>> result = 1;

		auto expCopy = exponent;
		auto baseCopy = base;
		
		while (expCopy > 0) {
			if ((expCopy & 1) == 1) {// exp. is odd
				result *= baseCopy;
			}
			baseCopy *= baseCopy;
			expCopy >>= 1; // y = y / 2;
		}
		return result;
	}

	// Complex base, complex exponent
	template <require::Complex rhs_type, typename = std::enable_if<!require::Integral<rhs_type>, void>::type>
	auto& exp(const require::Complex auto& base, const rhs_type& exponent) {}

	// Complex base, arithmetic exponent
	template <require::Arithmetic rhs_type, typename = std::enable_if<!(require::Integral<rhs_type> || require::Complex<rhs_type>), void>::type>
	auto& exp(const require::Complex auto& base, const rhs_type& exponent) {
	}

}