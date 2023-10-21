#pragma once
#include "../utilities/conventions.h"
#include "../utilities/template_traits.h"

#include <array>
#include <vector>

namespace duc::math_util::ex {
	
	namespace type {

		/// > Declarations

		template<satisfy::Integer digit_size = uint8_t, class container = std::vector<digit_size>>
		class basex;

		template<uint64_t bitsPerSection = 8, 
			class container = conditional::array_or_vector_256bmax<uint8_t, traits::fit_8bits<bitsPerSection>>>
		class numberx;


		/// > Definitions

		template<satisfy::Integer digit_size, class container>
		class basex {
			container _buffer;
		public:
			basex() {}
		};


		template<uint64_t bitsPerSection, class container>
		class numberx {
			container _buffer;

		public:
			numberx() {}


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
		[[nodiscard]] constexpr auto abs(const auto& num) noexcept { return num * ((num > 0) - (num < 0)); }


	}
}