#pragma once

#include "../utilities/conventions.h"
#include "../utilities/mutils.h"

namespace duc::alg {

	template<size_t max, size_t min = 0>
	class sequence {
	public:
		static constexpr size_t values = max - min + 1;

	public:
		static constexpr size_t size() { return values; }

		template<std::size_t ...I>
		static constexpr auto generateSequence(std::index_sequence<I...>) {
			return std::array<uint64_t, values> {(I + min)...};
		}
		static constexpr auto get() {
			return generateSequence(std::make_index_sequence<values>{});
		}
	};

	template<size_t max, size_t min = 2>
	class primes_array {
	public:
		static constexpr size_t values = max - min + 1;

	public:
		static constexpr size_t size() { return values; }

		template<size_t ...I>
		static constexpr auto generateSequence(std::index_sequence<I...>) {
			static_assert(max > min, "The max value must be greater than the min value.");
			static_assert(min > 0, "The min value must be greater than 0");

			constexpr auto all = sequence<max, min>::get();
			constexpr std::array<bool, values> mask = { isPrime(all[I], std::make_index_sequence<(((all[I] + 1) / 2) - 1)>{})... };
			constexpr size_t primesSize = (mask[I] + ...);
			std::array<size_t, primesSize> result = {};
			size_t i = 0;

			((mask[I] && ((result[i] = all[I]), i++)), ...);

			return result;
		}

		template<size_t ...I>
		static constexpr bool isPrime(size_t num, std::index_sequence<I...>) {
			return ((num % (I + 2)) &&...);
		}

		static constexpr auto get() {
			return generateSequence(std::make_index_sequence<values>{});
		}
	};
	
	template<size_t max>
	constexpr auto primesTo = primes_array<max>::get();
}