#pragma once

#include "../utilities/conventions.h"

namespace duc {
	namespace is {
		bool prime(satisfy::Integer auto n);
		bool even(satisfy::Integer auto  n);
		bool odd(satisfy::Integer auto  n);
		bool positive(satisfy::Integer auto  n);
		bool negative(satisfy::Integer auto  n);
		bool zero(satisfy::Integer auto  n);
		bool multiple(satisfy::Integer auto  n, satisfy::Integer auto  m);
		bool factor(satisfy::Integer auto  n, satisfy::Integer auto  m);
		bool divisor(satisfy::Integer auto  n, satisfy::Integer auto  m);
		bool multiple(satisfy::Integer auto  n, satisfy::Integer auto  m);
	}
	namespace get {
		auto digitsCount(satisfy::Integer auto  n);
		auto factorsCount(satisfy::Integer auto  n);
		auto divisorsCount(satisfy::Integer auto  n);
		auto multiplesCount(satisfy::Integer auto  n);


		auto factors(satisfy::Integer auto  n);
		auto divisors(satisfy::Integer auto  n);
		auto multiples(satisfy::Integer auto  n);
	}

	namespace has {
		bool nDigits(satisfy::Integer auto  n, satisfy::Integer auto  d);
		bool nFactors(satisfy::Integer auto  n, satisfy::Integer auto  f);
		bool nDivisors(satisfy::Integer auto  n, satisfy::Integer auto  d);
		bool nMultiples(satisfy::Integer auto  n, satisfy::Integer auto  m);
	}

}