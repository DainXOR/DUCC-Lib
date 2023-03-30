#pragma once

#include <concepts>
#include <type_traits>

#include "template_traits.h"

namespace duc::require {

	template<typename value_type>
	concept Integral = std::is_integral_v<value_type> && !std::is_same_v<value_type, bool>;

	template<typename value_type>
	concept UnsignedIntegral = Integral<value_type> && std::is_unsigned_v<value_type>;

	template<typename value_type>
	concept Decimal = std::is_floating_point_v<value_type>;

	template<typename value_type>
	concept Real = Integral<value_type> || Decimal<value_type>;

	template<typename value_type>
	concept Arithmetic = requires(value_type A, value_type B, double C) {

			{ A + B }; // -> std::convertible_to<value_type>;
			{ A - B }; // -> std::convertible_to<value_type>;
			{ A * B }; // -> std::convertible_to<value_type>;

			{ A + C }; // -> std::convertible_to<value_type>;
			{ A - C }; // -> std::convertible_to<value_type>;
			{ A * C }; // -> std::convertible_to<value_type>;
			{ A / C }; // -> std::convertible_to<value_type>;
		};

	template<typename value_type>
	concept Mathematical = Integral<value_type> || Decimal<value_type> || Arithmetic<value_type>;

	template<class vector_t>
	concept Vector = requires(vector_t v1, vector_t v2) {

		Arithmetic<vector_t>;

		// v1 * v2;
		// v1 * scalar;

		v1.normalize();
		v1.crossProduct(v2);

		v1.dimention();
		v1[uint64_t()];

		v1.fastMagnitude();
		v1.dotProduct(v2);

	};

	template<class matrix_t>
	concept Matrix = requires(matrix_t m) {
		m.rank() == 2;

	};

	template<uint16_t...args>
	concept Tensor = requires (int64_t n) {

		std::convertible_to<decltype(math_utils::vectorial_properties<args...>::rank), uint16_t>;
		std::convertible_to<decltype(math_utils::vectorial_properties<args...>::size), size_t>;

		math_utils::vectorial_properties<args...>::rank != 0;
		math_utils::vectorial_properties<args...>::size != 0;

		math_utils::vectorial_properties<args...>::dimentions[n];
		math_utils::vectorial_properties<args...>::dimentions.size();
	};
}

	
