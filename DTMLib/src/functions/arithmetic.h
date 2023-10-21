#pragma once
#include <unordered_map>

// #include <cmath>

#include "../utilities/conventions.h"
#include "../utilities/mutils.h"

namespace duc {

	const inline std::unordered_map<uint16_t, uint8_t> squares = {
		{4, 2}, {9, 3}, {16, 4}, {25, 5}, {36, 6}, {49, 7}, {64, 8}, {81, 9}, {100, 10}, {121, 11}, 
		{144, 12}, {169, 13}, {196, 14}, {225, 15}, {256, 16}, {289, 17}, {324, 18}, {361, 19}, {400, 20}, {441, 21}, 
		{484, 22}, {529, 23}, {576, 24}, {625, 25}, {676, 26}, {729, 27}, {784, 28}, {841, 29}, {900, 30}, {961, 31}, 
		{1024, 32}, {1089, 33}, {1156, 34}, {1225, 35}, {1296, 36}, {1369, 37}, {1444, 38}, {1521, 39}, {1600, 40}, {1681, 41}, 
		{1764, 42}, {1849, 43}, {1936, 44}, {2025, 45}, {2116, 46}, {2209, 47}, {2304, 48}, {2401, 49}, {2500, 50}, {2601, 51}, 
		{2704, 52}, {2809, 53}, {2916, 54}, {3025, 55}, {3136, 56}, {3249, 57}, {3364, 58}, {3481, 59}, {3600, 60}, {3721, 61}, 
		{3844, 62}, {3969, 63}, {4096, 64}, {4225, 65}, {4356, 66}, {4489, 67}, {4624, 68}, {4761, 69}, {4900, 70}, {5041, 71}, 
		{5184, 72}, {5329, 73}, {5476, 74}, {5625, 75}, {5776, 76}, {5929, 77}, {6084, 78}, {6241, 79}, {6400, 80}, {6561, 81}, 
		{6724, 82}, {6889, 83}, {7056, 84}, {7225, 85}, {7396, 86}, {7569, 87}, {7744, 88}, {7921, 89}, {8100, 90}, {8281, 91}, 
		{8464, 92}, {8649, 93}, {8836, 94}, {9025, 95}, {9216, 96}, {9409, 97}, {9604, 98}, {9801, 99}, {10000, 100}
	};

	// constexpr auto pow(const auto& base, const auto& exponent);

	/// \Todo	Write a better algorithm
	constexpr auto abs(satisfy::Decimal auto num) {
		return num < 0 ? -num : num;
	}
	constexpr auto abs(satisfy::Integer auto num) {
		constexpr uint16_t CHARBIT = 8;
		const int64_t mask = num >> (sizeof(decltype(num)) * CHARBIT - 1);
		return ((num + mask) ^ mask);
	}

	constexpr uint16_t digits(int64_t num) {
		uint16_t i = 0;
		do {
			num /= 10;
			i++;
		} while (num != 0);
		return i;
	}
	constexpr int64_t min(int64_t x, int64_t y) {
		return y ^ ((x ^ y) & -(x < y));
	}
	constexpr int64_t max(int64_t x, int64_t y) {
		return x ^ ((x ^ y) & -(x < y));
	}

	constexpr auto splitDecimal(satisfy::Real auto num) {
		return math_util::pair_any{ int64_t(num), num - int64_t(num) };
	}
	
	constexpr int64_t ceil(satisfy::Decimal auto number) {
		int8_t negativeFix = (number < 0) * -1;
		int8_t negativeSign = 1 + (number < 0) * -2;
		auto absNum = duc::abs(number);

		return negativeSign * int64_t(absNum + negativeFix + 1);
	}
	constexpr int64_t floor(satisfy::Decimal auto number) {
		int8_t negativeFix = (number < 0) * -1;
		return int64_t(number) + negativeFix;
	}
	constexpr int64_t round(satisfy::Decimal auto number) {
		return (number > 0 && number - int64_t(number) >= 0.5f) ||
			number < 0 && duc::abs(number) - duc::abs(int64_t(number)) <= 0.5f ?

			duc::ceil(number) :
			duc::floor(number);
	}
	constexpr double round(satisfy::Decimal auto number, uint16_t precision) {
		double decimals = duc::abs(number) - duc::abs(int64_t(number));
		uint16_t mult = math_util::powerPositiveInteger(10, precision);

		decimals *= mult;
		decimals = int64_t(decimals) / double(mult);

		return int64_t(number) + decimals;
	}
	
	constexpr double mod(double num, double div) {
		int64_t mult = duc::floor(num / div);
		return num - (div * double(mult));
	}

	constexpr auto greatestCommonDivisor(const auto& a, const auto& b) {
		return b == 0 ? a : duc::greatestCommonDivisor(b, duc::mod(a, b));
	}

	///	\Todo	Implement efficient algorith for each power case.

	constexpr double pow(satisfy::Real auto base, const satisfy::Integer auto& exponent) {
		if (exponent > 0) {
			if (exponent == 1 || base == 1)
				return base;

			return math_util::powerPositiveInteger(base, exponent);
		}
		
		if (exponent == 0)
			return 1;

		return math_util::powerPositiveInteger(1 / base, -exponent);
		
	}
	constexpr double pow(satisfy::Real auto base, const satisfy::Decimal auto& exponent) {
		return base * base;
	}

	//// Complex base, arithmetic exponent
	//auto pow(satisfy::StrictComplex auto base, const satisfy::Real auto& exponent) {
	//	return base * base * base;
	//}

	template<satisfy::Real real_type>
	constexpr double root(real_type base, const satisfy::Integer auto& exponent, double epsilon = 1e-4){
		if (exponent == 1 || base == 1 || base == 0)
			return base;

		const float invExponent = 1.0f / float(exponent);

		real_type prev = 5;
		real_type result = invExponent * ((exponent - 1) * prev + base / duc::pow(prev, exponent - 1));

		while (duc::abs(prev - result) > epsilon) {
			prev = result;
			result = invExponent * ((exponent - 1) * prev + base / duc::pow(result, exponent - 1));
		}

		return static_cast<double>(result);
	}


/// \Note	Quake fast inverse square root
/// \Effect	Be wary since this method uses some manipulation that leads to UB
///	\Warn	This method does not handle $x <= 0
/// 
	float fastInvSqrt(float x) {

		float xhalf = 0.5f * x;

		int i = *(int*)&x;              // get bits for floating value
		i = 0x5f375a86 - (i >> 1);      // gives initial guess y0
		x = *(float*)&i;                // convert bits back to float
		x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy

		return x;
	}

}