#pragma once
#include <type_traits>
#include <iostream>
#include <unordered_map>

// #include <cmath>

#include "../utilities/constrains.h"
#include "../utilities/dmutils.h"

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
	constexpr auto abs(const require::Decimal auto& num) {
		return num < 0 ? -num : num;
	}
	constexpr auto abs(const require::Integral auto& num) {
		constexpr uint16_t CHARBIT = 8;
		const uint16_t mask = num >> (sizeof(decltype(num)) * CHARBIT - 1);
		return ((num + mask) ^ mask);
	}

	constexpr auto splitDecimal(const require::Real auto& num) {
		return math_utils::pair_any{ int64_t(num), num - int64_t(num) };
	}

	constexpr int64_t ceil(const require::Decimal auto& number) {
		int8_t negativeFix = (number < 0) * -1;
		int8_t negativeSign = 1 + (number < 0) * -2;
		auto absNum = duc::abs(number);

		return negativeSign * int64_t(absNum + negativeFix + 1);
	}
	constexpr int64_t floor(const require::Decimal auto& number) {
		int8_t negativeFix = (number < 0) * -1;
		return int64_t(number) + negativeFix;
	}
	constexpr int64_t round(const require::Decimal auto& number) {
		return (number > 0 && number - int64_t(number) >= 0.5f) ||
			number < 0 && duc::abs(number) - duc::abs(int64_t(number)) <= 0.5f ?

			duc::ceil(number) :
			duc::floor(number);
	}
	constexpr double round(const require::Decimal auto& number, const uint16_t& precition) {
		double decimals = duc::abs(number) - duc::abs(int64_t(number));
		uint16_t mult = math_utils::powerPositiveInteger(10, precition);

		decimals *= mult;
		decimals = int64_t(decimals) / double(mult);

		return int64_t(number) + decimals;
	}
	
	constexpr double mod(const double& num, const double& div) {
		int64_t mult = duc::floor(num / div);
		return num - (div * mult);
	}


	///	\Todo	Implement efficient algorith for each power case.

	constexpr double pow(const require::Real auto& base, const require::Integral auto& exponent) {
		double result = 1;

		if (exponent > 0) {
			if (exponent == 1 || base == 1)
				return base;

			auto expCopy = exponent;
			auto baseCopy = base;

			return math_utils::powerPositiveInteger(baseCopy, expCopy);
		}
		
		if (exponent == 0)
			return result;

		auto invBase = 1 / base;
		auto posExp = -exponent;

		return math_utils::powerPositiveInteger(invBase, posExp);
		
	}

	// Complex base, complex exponent
	// template <require::Decimal rhs_type, typename = std::enable_if<!require::Integral<rhs_type>, void>::type>
	auto pow(const require::Real auto& base, const require::Decimal auto& exponent) {
		return base * base;
	}

	//// Complex base, arithmetic exponent
	//template <require::Arithmetic rhs_type, typename = std::enable_if<!(require::Integral<rhs_type> || require::Complex<rhs_type>), void>::type>
	//auto pow(const require::Complex auto& base, const rhs_type& exponent) {
	//	return base * base * base;
	//}


	constexpr float root(require::Real auto base, const require::Integral auto& exponent, double epsilon = 1e-4){
		if (exponent == 1 || base == 1)
			return base;

		float prev = 5;
		float result = (1.0 / exponent) * ((exponent - 1) * prev + base / duc::pow(prev, exponent - 1));

		while (duc::abs(prev - result) > epsilon) {
			prev = result;
			result = (1.0 / exponent) * ((exponent - 1) * prev + base / duc::pow(result, exponent - 1));
		}

		return result;
	}


/// \Note	Quake fast inverse square root
/// \Effect	Be wary since this method uses some manipulation that leads to UB
///			This method does not handle $x == 0
	float fastInvSqrt(float x) {

		float xhalf = 0.5f * x;

		int i = *(int*)&x;              // get bits for floating value
		i = 0x5f375a86 - (i >> 1);      // gives initial guess y0
		x = *(float*)&i;                // convert bits back to float
		x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy

		return x;
	}

}