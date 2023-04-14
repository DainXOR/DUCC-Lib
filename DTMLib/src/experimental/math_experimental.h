#pragma once
#include "../utilities/constrains.h"
#include "../utilities/template_traits.h"

#include <array>
#include <vector>

namespace duc::math_utils::experimental {

	template<require::Real type>
	class extended_base {
		std::vector<uint64_t>
	public:
		extended_base(){}
	};

	template<require::Real type, uint64_t bits>
	class number {
		uint64_t n = (bits >> 3) + (bits % 8 > 0);
		std::array<uint8_t, n> _buffer;

	public:
		number() {}


	};

}