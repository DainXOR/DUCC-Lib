#pragma once
#include <stdint.h>
#include <string>
#include <cmath>

#include "utils_declarations.h"

namespace duc::util {

	template<auto v>
	using type_of = decltype(v);

	template<class t>
	struct type_info {
		using type = t;
		static constexpr const char* name = typeid(type).name();
		static constexpr size_t size = sizeof(type);

		static constexpr bool isConstexpr = true;
		static constexpr bool isAggregate = std::is_aggregate_v<type>;
	};

	template<auto v>
	struct var_info {
		using type = type_of<v>;
		static constexpr const char* name = typeid(type).name();
		static constexpr size_t size = sizeof(v);

		static constexpr bool isConstexpr = noexcept(v);
		static constexpr bool isAggregate = std::is_aggregate_v<type>;
	};
	
	template<auto ...v>
	struct expansion {};
	
	namespace {
		template<int64_t end, int64_t begin, int64_t step, template<class, auto...> class predicate, int64_t n0, int64_t ...n> 
			requires (step != 0 && satisfy::ConstexprCallable<predicate, bool, int64_t>)
		constexpr auto sequenceGenerator() {

			if constexpr (step > 0) {
				static_assert(begin < end, "The starting value must be smaller than the end value.");

				if constexpr (n0 + step > end) {
					if constexpr (predicate<bool, begin>{}()) return expansion<n..., begin>{};
					else return expansion<n...>{};
				}
				else {
					if constexpr (predicate<bool, n0 + step>{}())
						return sequenceGenerator<end, begin, step, predicate, n0 + step, n0 + step, n...>();
					else
						return sequenceGenerator<end, begin, step, predicate, n0 + step, n...>();
				}
			}
			else {
				static_assert(begin > end, "The starting value must be bigger than the end value.");

				if constexpr (n0 + step < end) {
					if constexpr (predicate<bool, begin>{}()) return expansion<n..., begin>{};
					else return expansion<n...>{};
				}
				else {
					if constexpr (predicate<bool, n0 + step>{}())
						return sequenceGenerator<end, begin, step, predicate, n0 + step, n0 + step, n...>();
					else
						return sequenceGenerator<end, begin, step, predicate, n0 + step, n...>();
				}
			}
		}
		
		template<auto ...v>
		constexpr duc::util::expansion<v...> unrollExpansions(duc::util::expansion<v...> ex) {
			return ex;
		}
		template<auto ...iv, auto...ov>
		constexpr auto unrollExpansions(duc::util::expansion<iv...>, duc::util::expansion<ov...>, auto ...v) {
			return unrollExpansions(duc::util::expansion<iv..., ov...>{}, v...);
		}

		template<int count, auto ... args>
		constexpr auto origin() {
			if constexpr (count <= 1) return duc::util::expansion<args...>{};
			else return replicator<count - 1>(duc::util::expansion<args...>{}, duc::util::expansion<args...>{});
		}
		template<int count, auto ... args, auto ... args2>
		constexpr auto replicator(duc::util::expansion<args...> o, duc::util::expansion<args2...>) {
			if constexpr (count <= 1) return duc::util::expansion<args..., args2...>{};
			else return replicator<count - 1>(o, duc::util::expansion<args..., args2...>{});
		}

		template<int64_t number>
		constexpr bool isPrime() {
			constexpr int64_t absValue = number * ((number > 0) - (number < 0));
			if constexpr (absValue <= 1) return false;
			else {
				if constexpr (absValue <= 3) return true;
				else {
					constexpr int64_t minTries = absValue < 10 ? absValue - 1 : ((absValue + 1) / 2) - 1;
					return isPrime(absValue, sequence<minTries, 2>);
				}

			}
		}

		template<auto ...I>
		constexpr bool isPrime(int64_t num, expansion<I...>) {
			return ((num % I) &&...);
		}
	}

	template<class, auto...>
	struct yes {
		constexpr bool operator()() {
			return true;
		}
	};
	template<class, auto...>
	struct no {
		constexpr bool operator()() {
			return false;
		}
	};
	template<class, int64_t number>
	struct is_prime {
		constexpr bool operator()() {
			return isPrime<number>();
		}
	};

	template<int64_t end, int64_t begin, int64_t step, template<class, auto...> class predicate>
		requires (step != 0 && satisfy::ConstexprCallable<predicate, bool, int64_t>)
	class sequence_array {
	public:
		static constexpr size_t values = (end - begin + 1) / step;

	public:
		static constexpr size_t size() { return values; }

		template<int64_t ...I>
		static constexpr std::array<int64_t, values> generateSequence(expansion<I...>) {
			return std::array<int64_t, values> { I... };
		}
		static constexpr std::array<int64_t, values> get() {
			return generateSequence(sequenceGenerator<end, begin, step, predicate, begin>());
		}
	};
	template<int64_t end, int64_t begin, int64_t step>
	class primes_array : sequence_array<end, begin, step, is_prime> {};




	template<typename ...str>
	constexpr std::string concat(std::string arg1, str... args) {
		std::string result = arg1 + (std::string(args) + ...);
		return result;
	}


	std::string toChars(int64_t num) {
		/*
		char* numString = new char[32];
		const uint16_t NumLenght = digits(num);
		bool isPositive = num >= 0;
		num = duc::abs(num);

		for (int i = NumLenght - isPositive; i >= 0; i--, num /= 10) {
			numString[i] = (num % 10) + '0';
		}

		!isPositive ? numString[0] = '-' : 0;
		numString[NumLenght + !isPositive] = '\0';
		*/

		return std::to_string(num);
	}
	std::string toChars(double num, uint16_t precision) {
		/*
		auto [integer, decimals] = duc::splitDecimal(num);
		decimals = duc::abs(decimals);
		int64_t intDecimals = int64_t(decimals * duc::pow(10, precision));
		bool isNegative = num < 0;

		char* numString = nullptr;

		if (integer == 0 && isNegative) {
			numString = new char[32];
			numString[0] = '-';
			numString[1] = '0';
			numString[2] = '\0';
		}
		else {
			numString = duc::toChars(integer);
		}


		char* decString = duc::toChars(intDecimals);
		uint16_t intSize = duc::digits(integer) + isNegative;

		numString[intSize++] = '.';

		for (int i = 0; i < precision; i++) {
			numString[intSize + i] = decString[i];
		}

		delete[] decString;

		numString[intSize + precision] = '\0';
		*/

		double multiplier = std::pow(10, precision);
		return std::to_string(std::floor(num * multiplier) / multiplier);
	}
}

