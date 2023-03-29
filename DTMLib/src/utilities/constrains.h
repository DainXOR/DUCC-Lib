#pragma once

#include <concepts>
#include <type_traits>
#include <array>

namespace duc::math_utils {
	namespace helper {

				template<uint16_t... dimentions>
				constexpr uint16_t tensor_rank = sizeof...(dimentions);

				template<size_t... dimentions>
				constexpr size_t tensor_size = (... * dimentions);

				template<uint16_t... dimentions>
				constexpr std::array<size_t, tensor_rank<dimentions...>> tensor_dimentions = { dimentions... };

				template<uint64_t... dims>
				struct vectorial_properties {
					constexpr static uint16_t	rank = tensor_rank<dims...>;
					constexpr static size_t		size = tensor_size<dims...>;
					constexpr static auto		dimentions = tensor_dimentions<dims...>;

				};

				template<uint64_t... dims>
				struct _CRT_DEPRECATE_TEXT("This struct is for testing purpose only and will be eliminated. Use 'vectorial_properties' instead.")
					tensor_properties_struct {
					uint16_t									rank = tensor_rank<dims...>;
					size_t										size = tensor_size<dims...>;
					std::array<size_t, tensor_rank<dims...>>	dimentions = tensor_dimentions<dims...>;

				};

			}


	namespace require {

		template<typename value_type>
		concept Integral = std::is_integral_v<value_type> && !std::is_same_v<value_type, bool>;

		template<typename value_type>
		concept Decimal = std::is_floating_point_v<value_type>;

		template<typename value_type>
		concept UnsignedIntegral = Integral<value_type> && std::is_unsigned_v<value_type>;

		namespace {
			template<typename value_type>	// Had to declare this structure so the concept above works
			struct is_arithmetic {
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

			//std::cout << A;
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

			std::convertible_to<decltype(helper ::vectorial_properties<args...>::rank), uint16_t>;
			std::convertible_to<decltype(helper::vectorial_properties<args...>::size), size_t>;

			std::is_assignable_v<
				std::array<size_t, helper::vectorial_properties<args...>::size>,
				decltype(helper::vectorial_properties<args...>::dimentions)
			>;

			helper::vectorial_properties<args...>::rank != 0;
			helper::vectorial_properties<args...>::size != 0;

			helper::vectorial_properties<args...>::dimentions[n];
			helper::vectorial_properties<args...>::dimentions.size();
		};


		
	}
}

	
