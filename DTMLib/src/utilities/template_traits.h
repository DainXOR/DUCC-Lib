#pragma once

#include <type_traits>
#include <concepts>
#include <array>
#include <vector>
#include <numeric>

namespace duc {
	namespace trait {

		template<uint16_t... dimentions>
		constexpr uint16_t vectorial_rank = sizeof...(dimentions);

		template<size_t... dimentions>
		constexpr size_t vectorial_size = vectorial_rank<dimentions...> ? (dimentions * ...) : 0;

		template<uint16_t... dimentions>
		constexpr std::array<uint16_t, vectorial_rank<dimentions...>> vectorial_shape = { dimentions... };

		template<uint64_t... dimentions>
		struct vectorial {
			static constexpr uint16_t	rank = vectorial_rank<dimentions...>;
			static constexpr size_t		size = vectorial_size<dimentions...>;
			static constexpr auto		shape = vectorial_shape<dimentions...>;

		};


		template<size_t size_ask, size_t section_size>
		struct adjust_to_fit {
			static constexpr size_t size = (size_ask >> 3) + (size_ask % section_size > 0);
		};

		template<size_t size_ask>
		constexpr size_t fit_8bits = adjust_to_fit<size_ask, 8>;
		template<size_t size_ask>
		constexpr size_t fit_16bits = adjust_to_fit<size_ask, 16>;
		template<size_t size_ask>
		constexpr size_t fit_32bits = adjust_to_fit<size_ask, 32>;
		template<size_t size_ask>
		constexpr size_t fit_64bits = adjust_to_fit<size_ask, 64>;

	}

	namespace conditional {

		template<size_t size_ask, size_t bytes_cap, typename type>
		struct size_cap {
			static constexpr bool value = size_ask && (size_ask < ((1 << bytes_cap) / sizeof(type)));
		};

		template<template<size_t, typename> class conditional, size_t size, typename contained_type, class cont_1, class cont_2>
		struct conditional_container {
			using type = std::conditional_t<conditional<size, contained_type>::value, cont_1, cont_2>;
		};

		template<size_t size, typename type>
		using max8b = size_cap<size, 3, type>;
		template<size_t size, typename type>
		using max16b = size_cap<size, 4, type>;
		template<size_t size, typename type>
		using max32b = size_cap<size, 5, type>;
		template<size_t size, typename type>
		using max64b = size_cap<size, 6, type>;
		template<size_t size, typename type>
		using max128b = size_cap<size, 7, type>;
		template<size_t size, typename type>
		using max256b = size_cap<size, 8, type>;
		template<size_t size, typename type>
		using max512b = size_cap<size, 9, type>;
		template<size_t size, typename type>
		using max1kb = size_cap<size, 10, type>;
		template<size_t size, typename type>
		using max1mb = size_cap<size, 20, type>;
		template<size_t size, typename type>
		using max1gb = size_cap<size, 30, type>;


		template<size_t size, typename contained_type, class cont_1, class cont_2>
		using container_32bmax = conditional_container<max32b, size, contained_type, cont_1, cont_2>;
		template<size_t size, typename contained_type, class cont_1, class cont_2>
		using container_64bmax = conditional_container<max64b, size, contained_type, cont_1, cont_2>;
		template<size_t size, typename contained_type, class cont_1, class cont_2>
		using container_128bmax = conditional_container<max128b, size, contained_type, cont_1, cont_2>;
		template<size_t size, typename contained_type, class cont_1, class cont_2>
		using container_256bmax = conditional_container<max256b, size, contained_type, cont_1, cont_2>;
		template<size_t size, typename contained_type, class cont_1, class cont_2>
		using container_512bmax = conditional_container<max512b, size, contained_type, cont_1, cont_2>;
		template<size_t size, typename contained_type, class cont_1, class cont_2>
		using container_1kbmax = conditional_container<max1kb, size, contained_type, cont_1, cont_2>;
		template<size_t size, typename contained_type, class cont_1, class cont_2>
		using container_1mbmax = conditional_container<max1mb, size, contained_type, cont_1, cont_2>;
		template<size_t size, typename contained_type, class cont_1, class cont_2>
		using container_1gbmax = conditional_container<max1gb, size, contained_type, cont_1, cont_2>;

		template<typename contained_type, size_t size>
		using array_or_vector_64bmax = container_64bmax<size, contained_type, std::array<contained_type, size>, std::vector<contained_type>>::type;
		template<typename contained_type, size_t size>
		using array_or_vector_128bmax = container_128bmax<size, contained_type, std::array<contained_type, size>, std::vector<contained_type>>::type;
		template<typename contained_type, size_t size>
		using array_or_vector_256bmax = container_256bmax<size, contained_type, std::array<contained_type, size>, std::vector<contained_type>>::type;
		template<typename contained_type, size_t size>
		using array_or_vector_512bmax = container_512bmax<size, contained_type, std::array<contained_type, size>, std::vector<contained_type>>::type;
		template<typename contained_type, size_t size>
		using array_or_vector_1kbmax = container_1kbmax<size, contained_type, std::array<contained_type, size>, std::vector<contained_type>>::type;
		template<typename contained_type, size_t size>
		using array_or_vector_1mbmax = container_1mbmax<size, contained_type, std::array<contained_type, size>, std::vector<contained_type>>::type;
		template<typename contained_type, size_t size>
		using array_or_vector_1gbmax = container_1gbmax<size, contained_type, std::array<contained_type, size>, std::vector<contained_type>>::type;


	}
}