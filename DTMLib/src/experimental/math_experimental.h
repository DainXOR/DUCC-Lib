#pragma once
#include <macro_tools.h>
#include "../functions/algorithm.h"
#include "../utilities/conventions.h"
#include "../utilities/template_traits.h"

#include <array>
#include <vector>
#include <map>

namespace duc::ex {
	
	namespace type {

		/// > Declarations

		template<satisfy::Integer digit_size = uint8_t, class container = std::vector<digit_size>>
		class basex;

		template<size_t size8BitNums = 16, uint64_t bitsPerSection = 8,
			class container = conditional::array_or_vector_256bmax<uint8_t, traits::fit_8bits<bitsPerSection>>>
		class numberx;

		template<satisfy::UnsignedInteger number_t, size_t max2Pow = 64, size_t precision = 5>
		class multy_number;

		/// > Definitions

		template<satisfy::Integer digit_size, class container>
		class basex {
		public:
			container _buffer;
		public:
			basex() {}
		};


		template<size_t size8BitNums, uint64_t bitsPerSection, class container>
		class numberx {
		public:
			container _buffer;

		public:
			numberx() {}


		};

		template<satisfy::UnsignedInteger number_t, size_t max2Pow, size_t precision>
		class multy_number {
		public:
			size_t buffer = 1;
			size_t storedCount = 0;
			type::numberx<max2Pow / 8> buffer;

			constexpr static size_t maxPrime = 11 * (float(max2Pow) / 64);
			constexpr static size_t primeCount = duc::alg::primesTo<maxPrime>.size();


		public:
			bool contains(number_t number) {
				for (auto p : duc::alg::primesTo<maxPrime>) {
					size_t count = 0;
					size_t aux = this->buffer;

					while (duc::mod(aux, p) <= duc::mutil::error<precision>) {
						aux /= p;
						count++;
					}

					if (count == number) {
						return true;
					}
				}
				return false;
			}

			bool add(number_t number) {
				if (primeCount <= this->storedCount || this->contains(number))
					return false;
				
				size_t prime = duc::alg::primesTo<maxPrime>[this->storedCount];
				this->buffer *= duc::pow(prime, number);
				this->storedCount++;
				return true;
			}
			bool remove(number_t number) {
				for (auto p : duc::alg::primesTo<maxPrime>) {
					size_t count = 0;
					size_t aux = this->buffer;

					while (duc::mod(aux, p) <= duc::mutil::error<precision>) {
						aux /= p;
						count++;
					}

					if (count == number) {
						this->buffer = aux;
						return true;
					}
				}
				return false;
			}

			number_t retrieve(size_t pos) {
				size_t p = duc::alg::primesTo<maxPrime>[pos];
				size_t count = 0;
				size_t aux = this->buffer;

				while (duc::mod(aux, p) <= duc::mutil::error<precision>) {
					aux /= p;
					count++;
				}

				return count;
			}
			auto retrieveAll() {
				std::array<number_t, primeCount> values = {};

				for (size_t i = 0; i < primeCount; i++) {
					size_t p = duc::alg::primesTo<maxPrime>[i];
					size_t count = 0;
					size_t aux = this->buffer;

					while (duc::mod(aux, p) <= duc::mutil::error<precision>) {
						aux /= p;
						count++;
					}

					values[i] = count;
				}
				return values;
			}

			bool reencode() {
				auto values = this->retrieveAll(); // Sort values (n > 0)


				return false;
			}
		};
	}

	
	
	namespace function {

		template<auto n, auto a, uint8_t step>
		struct factorial_helper {
			static constexpr auto value =
				factorial_helper<
				(n > step && step > 0) * (n - step),
				a * n,
				step>::value;
		};

		template<auto a, uint8_t step>
		struct factorial_helper<0, a, step> {
			static constexpr auto value = a;
		};

		template<auto n, uint8_t step>
		struct factorial_s {
			static constexpr auto value = factorial_helper<n, 1, step>::value;
		};

		//template<>
		//struct perfect_sqr_down {
		//
		//};
		//
		//template<auto n, auto a, auto step>
		//struct sqrt_helper {
		//	static constexpr double value = n + ;
		//};
		//
		//using namespace dmutils::template_traits;
		//template<Float num_type, num_type n, num_type step>
		//struct sqrt_s {
		//	static constexpr double value = sqrt_helper<n, tr>::value;
		//};

		template<auto n>
		constexpr auto factorial = factorial_s<n, 1>::value;

		template<auto n>
		constexpr auto factorial_double = factorial_s<n, 2>::value;

		template<auto n, auto step>
		constexpr auto factorial_n = factorial_s<n, step>::value;

		//template<auto n, Float num_type = float>
		//constexpr num_type sqrt = sqrt_s<num_type, n, 1>::value;

	}
	
	namespace migration {


	}
}