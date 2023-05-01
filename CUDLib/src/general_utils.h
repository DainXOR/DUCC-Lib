#pragma once

#include <stdint.h>
#include <string>
#include <cmath>

namespace duc::util {

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

