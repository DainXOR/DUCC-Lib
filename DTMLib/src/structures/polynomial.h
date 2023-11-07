#pragma once

#include "../functions/arithmetic.h"

#include "../utilities/conventions.h"
#include "../utilities/mutils.h"

namespace duc {

	template<satisfy::Complex type1 = double, satisfy::Complex type2 = double>
	class fraction {
	public:
		using num_type = type1;
		using den_type = type2;

		num_type numerator;
		den_type denominator;

	public:
		constexpr bool checkDenominator() const noexcept {
			return this->denominator != 0;
		}

		constexpr num_type toDecimal() const noexcept {
			return this->numerator / this->denominator;
		}

		template<typename rhs_num, typename rhs_den, typename lhs_num, typename lhs_den> 
		static constexpr bool 
		equivalent(const fraction<lhs_num, lhs_den>& lhs, const fraction<rhs_num, rhs_den>& rhs, const double& epsilon = 1e-5) noexcept {
			return (lhs.toDecimal() - rhs.toDecimal()) <= epsilon;
		}
		template<typename rhs_num, typename rhs_den>
		constexpr bool equivalent(const fraction<rhs_num, rhs_den>& rhs, const double& epsilon = 1e-5) const noexcept {
			return (this->toDecimal() - rhs.toDecimal()) <= epsilon;
		}

		template<typename rhs_num, typename rhs_den>
		bool operator==(const fraction<rhs_num, rhs_den>& rhs) {
			return this->equivalent(rhs, 1e-9);
		}

		template<typename rhs_num, typename rhs_den>
		fraction operator+(const fraction<rhs_num, rhs_den>& rhs) const noexcept {
			return { this->numerator + rhs.numerator, this->denominator + rhs.denominator };
		}
		fraction operator+(const satisfy::Real auto& rhs) const noexcept {
			return this + fraction<num_type, den_type>::toFraction(rhs);
		}
		
	};

	template<satisfy::Real num_type = double, satisfy::Real den_type = double>
	fraction<num_type, den_type> toFraction(const satisfy::Real auto& number, double epsilon = 1e-5) DUC_RNOEXCEPT {

		auto [intPart, fracPart] = duc::splitDecimal(number);

		if (duc::abs(fracPart) < epsilon) {
			return { static_cast<num_type>(intPart), 1 };
		}

		double numberCopy = number;
		double p = 0, p0 = 0, p1 = 1, p2;
		double q = 0, q0 = 1, q1 = 0, q2;
		double error = 0;

		for (uint16_t i = 0;; i++) {

			p = intPart * p1 + p0;
			q = intPart * q1 + q0;
			error = duc::abs(number - (p / q));

			if ((i & 1) && error < epsilon) {
				DUC_INFO_LOG(i + 1);
				return { static_cast<num_type>(p1), static_cast<den_type>(q1) };
			}

			p2 = p1;
			q2 = q1;
			p1 = p;
			q1 = q;
			p0 = p2;
			q0 = q2;
			numberCopy = 1.0 / (numberCopy - intPart);
			intPart = duc::floor(numberCopy);
		}
	}

	template<satisfy::StrictComplex complex_type>
	fraction<complex_type> toFraction(const complex_type& number) DUC_RNOEXCEPT {
		fraction realFrac = duc::toFraction(number.real());
		fraction imgFrac = duc::toFraction(number.img());
		auto gcd = duc::greatestCommonDivisor(realFrac.denominator, imgFrac.denominator);

		auto imgMult = realFrac.denominator / gcd;
		auto realMult = imgFrac.denominator / gcd;

		realFrac.numerator *= realMult;
		imgFrac.numerator *= imgMult;

		auto resultDen = realFrac.denominator * imgMult;

		complex_type resultNum(realFrac.numerator, imgFrac.numerator);

		return { resultNum , resultDen };
	}

	template<satisfy::Complex type = double>
	class polynomial {
	public:
		using ec_type = char*;
		using va_type = duc::pair_any<char, type>[];


	public:
		ec_type expretion;
		va_type values;
	};
}