#pragma once

#include "../"

namespace duc::ex {

	template<size_t desiredSize, size_t minBytes>
	struct min_type {
		using type = uint8_t;
	};


}