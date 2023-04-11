#pragma once

#include <concepts>
#include <type_traits>

#include "template_traits.h"
// condition | convention | standard | satisfy 
namespace duc::require { 

	template<typename value_type>
	concept Integer = std::is_integral_v<value_type> && !std::is_same_v<value_type, bool>;

	template<typename value_type>
	concept UnsignedInteger = Integer<value_type> && std::is_unsigned_v<value_type>;

	template<typename value_type>
	concept Decimal = std::is_floating_point_v<value_type>;

	template<typename value_type>
	concept Real = Integer<value_type> || Decimal<value_type>;

	template<typename value_type>
	concept Arithmetic = requires(value_type A, value_type B, double C) {
			{ A + B }; // -> std::convertible_to<value_type>;
			{ A - B }; // -> std::convertible_to<value_type>;
			{ A * B }; // -> std::convertible_to<value_type>;
			{ A / B }; // -> std::convertible_to<value_type>;

			{ A + C }; // -> std::convertible_to<value_type>;
			{ A - C }; // -> std::convertible_to<value_type>;
			{ A * C }; // -> std::convertible_to<value_type>;
			{ A / C }; // -> std::convertible_to<value_type>;

			{ A <=> B }; // -> std::convertible_to<value_type>;
			{ A <=> C }; // -> std::convertible_to<value_type>;
		};

	template<typename value_type>
	concept Complex = requires(value_type A, value_type B) {
		Real<value_type> || Arithmetic<value_type>;

		{ A + B } -> std::convertible_to<value_type>;
		{ A - B } -> std::convertible_to<value_type>;
		{ A * B } -> std::convertible_to<value_type>;
		{ A / B } -> std::convertible_to<value_type>;

		A = double();
	};

	template<typename value_type>
	concept StrictComplex = requires (value_type A) {
		Complex<value_type>;
		A.real();
		A.img();
	};

	template<class vector_t>
	concept Vector = requires(vector_t V1, vector_t V2, double S) {

		{ V1 + V2 }; // -> std::convertible_to<value_type>;
		{ V1 - V2 }; // -> std::convertible_to<value_type>;
		{ V1 * V2 }; // -> std::convertible_to<value_type>;

		{ V1 + S }; // -> std::convertible_to<value_type>;
		{ V1 - S }; // -> std::convertible_to<value_type>;
		{ V1 * S }; // -> std::convertible_to<value_type>;
		{ V1 / S }; // -> std::convertible_to<value_type>;

		// V1 * V2;
		// V1 * scalar;

		V1.dimention();
		V1.norm();
		V1.normalize();
		V1.crossProduct(V2);
		V1.dotProduct(V2);

		V1[uint64_t()];

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

		math_utils::vectorial_properties<args...>::shape[n];
		math_utils::vectorial_properties<args...>::shape.size();
	};

	template<typename space_t>
	concept VectorialSpace = requires(space_t S1) {
		S1.innerProduct();
	};

	template<typename value_type>
	concept Vectorial = Vector<value_type> || Matrix<value_type> || Tensor<> || VectorialSpace<value_type>;
}

	
