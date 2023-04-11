#pragma once

#include <array>

namespace duc::math_utils {

	template<uint16_t... dimentions>
	constexpr uint16_t str_rank = sizeof...(dimentions);

	template<size_t... dimentions>
	constexpr size_t str_size = str_rank<dimentions...> ? (dimentions * ...) : 0;

	template<uint16_t... dimentions>
	constexpr std::array<uint16_t, str_rank<dimentions...>> str_dimentions = { dimentions... };

	template<uint64_t... dims>
	struct vectorial_properties {
		constexpr static uint16_t	rank = str_rank<dims...>;
		constexpr static size_t		size = str_size<dims...>;
		constexpr static auto		shape = str_dimentions<dims...>;

	};

}
