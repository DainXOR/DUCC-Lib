#pragma once

namespace duc {
	template<int ov = -1>
	double sin(double value) noexcept{
		if (value < 1) {
			return sin<0>(value);
		}
	}
	template<>
	double sin<0>(double value) noexcept {
		return value - 0.1 * value;
	}
	template<>
	double sin<1>(double value) noexcept {
		return value;
	}

	double cos(double value) noexcept{
	}
	double tan(double value) noexcept{
	}
	double asin(double value) noexcept{
	}
	double acos(double value) noexcept{
	}
	double atan(double value) noexcept{
	}
	double sihn(double value) noexcept{
	}
	double cosh(double value) noexcept{
	}
	double tanh(double value) noexcept{
	}

}
