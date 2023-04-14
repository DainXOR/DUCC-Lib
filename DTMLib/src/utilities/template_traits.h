#pragma once

#include <type_traits>
#include <array>
#include <vector>

namespace duc {
	namespace math_utils {

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

	namespace conditional{

		template<size_t size_ask, size_t two_power, typename type>
		struct size_cap {
			static constexpr bool allowed = size_ask && (size_ask < ((1 << two_power) / sizeof(type)));
		};

		template<size_t size, typename type>
		using max8b = size_cap<size, 3, type>::allowed;
		template<size_t size, typename type>
		using max16b = size_cap<size, 4, type>::allowed;
		template<size_t size, typename type>
		using max32b = size_cap<size, 5, type>::allowed;
		template<size_t size, typename type>
		using max64b = size_cap<size, 6, type>::allowed;
		template<size_t size, typename type>
		using max128b = size_cap<size, 7, type>::allowed;
		template<size_t size, typename type>
		using max256b = size_cap<size, 8, type>::allowed;
		template<size_t size, typename type>
		using max512b = size_cap<size, 9, type>::allowed;
		template<size_t size, typename type>
		using max1mb = size_cap<size, 10, type>::allowed;


		template<template<size_t, typename> class conditional, size_t size, typename contained_type, class cont_1, class cont_2>
		struct conditional_container {
			using type = std::conditional_t<conditional<size, type>, cont_1, cont_2>;
		};


		template<size_t size, typename contained_type, class cont_1, class cont_2>
		using container32b_max = conditional_container<max32b, size, contained_type, cont_1, cont_2>;
		template<size_t size, typename contained_type, class cont_1, class cont_2>
		using container64b_max = conditional_container<max64b, size, contained_type, cont_1, cont_2>;
		template<size_t size, typename contained_type, class cont_1, class cont_2>
		using container128b_max = conditional_container<max128b, size, contained_type, cont_1, cont_2>;
		template<size_t size, typename contained_type, class cont_1, class cont_2>
		using container256b_max = conditional_container<max256b, size, contained_type, cont_1, cont_2>;
		template<size_t size, typename contained_type, class cont_1, class cont_2>
		using container512b_max = conditional_container<max512b, size, contained_type, cont_1, cont_2>;
		template<size_t size, typename contained_type, class cont_1, class cont_2>
		using container1mb_max = conditional_container<max1mb, size, contained_type, cont_1, cont_2>;

		template<size_t size, typename contained_type>
		using array_or_vector_64bmax = container64b_max<size, contained_type, std::array<contained_type, size>, std::vector<contained_type>>::type;
		template<size_t size, typename contained_type>
		using array_or_vector_128bmax = container128b_max<size, contained_type, std::array<contained_type, size>, std::vector<contained_type>>::type;
		template<size_t size, typename contained_type>
		using array_or_vector_256bmax = container256b_max<size, contained_type, std::array<contained_type, size>, std::vector<contained_type>>::type;
		template<size_t size, typename contained_type>
		using array_or_vector_512bmax = container512b_max<size, contained_type, std::array<contained_type, size>, std::vector<contained_type>>::type;
		template<size_t size, typename contained_type>
		using array_or_vector_1mbmax = container1mb_max<size, contained_type, std::array<contained_type, size>, std::vector<contained_type>>::type;
	}

	

}
