#pragma once

#include "arithmetic.h"

#include "../utilities/constrains.h"
#include "../utilities/mutils.h"

namespace duc {

	auto greatestCommonDivisor(const auto& a, const auto& b) {
		return b == 0 ? a : duc::greatestCommonDivisor(b, duc::mod(a, b));
	}
}