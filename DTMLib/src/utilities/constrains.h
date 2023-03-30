#pragma once

#include <concepts>
#include <type_traits>

#include "template_traits.h"

namespace duc::math_utils {
	namespace require {

		template<typename value_type>
		concept Integral = std::is_integral_v<value_type> && !std::is_same_v<value_type, bool>;

		template<typename value_type>
		concept Decimal = std::is_floating_point_v<value_type>;

		template<typename value_type>
		concept UnsignedIntegral = Integral<value_type> && std::is_unsigned_v<value_type>;

		namespace {
			template<typename value_type>	// Had to declare this structure so the concept above works
			struct _CRT_DEPRECATE_TEXT("Marked for delete.")
				is_arithmetic {
				static constexpr bool value = Arithmetic<value_type>;
			};
		}

		template<typename value_type>
		concept Real = Integral<value_type> || Decimal<value_type>;

		template<typename value_type>
		concept Arithmetic = requires(value_type A, value_type B, double C) {

			{ A + B } -> std::convertible_to<value_type>;
			{ A - B } -> std::convertible_to<value_type>;
			{ A * B } -> std::convertible_to<value_type>;
			//{ A / B } -> std::convertible_to<value_type>; // We will see

			{ A + C } -> std::convertible_to<value_type>;
			{ A - C } -> std::convertible_to<value_type>;
			{ A * C } -> std::convertible_to<value_type>;
			{ A / C } -> std::convertible_to<value_type>;

			//std::disjunction_v<
			//	std::is_same<value_type, decltype(A + B)>,
			//	is_arithmetic<decltype(A + B)>>; // Could not use concept here
		};

		template<typename value_type>
		concept Mathematical = requires() {
			Integral<value_type> || Decimal<value_type> || Arithmetic<value_type>;
		};

		template<class vector_t>
		concept Vector = requires(vector_t v1, vector_t v2) {

			Arithmetic<vector_t>;

			// v1 * v2;
			// v1 * scalar;

			v1.normalize();
			v1.crossProduct(v2);

			v1.dimention();
			v1[uint64_t()];

			v1.magnitude();
			v1.dotProduct(v2);

		};

		template<class matrix_t>
		concept Matrix = requires(matrix_t m) {
			m.rank() == 2;

		};

		template<uint16_t...args>
		concept Tensor = requires (int64_t n) {

			std::convertible_to<decltype(template_traits::vectorial_properties<args...>::rank), uint16_t>;
			std::convertible_to<decltype(template_traits::vectorial_properties<args...>::size), size_t>;

			template_traits::vectorial_properties<args...>::rank != 0;
			template_traits::vectorial_properties<args...>::size != 0;

			template_traits::vectorial_properties<args...>::dimentions[n];
			template_traits::vectorial_properties<args...>::dimentions.size();
		};


		
	}
}

	
