#pragma once

#include <math.h>

#include "../utilities/constrains.h"

namespace duc{

	template<require::Arithmetic type, require::Integral auto m, require::Integral auto n>
	class matrix;

	template<require::UnsignedIntegral auto r, require::Mathematical type>
	class vector {
	public:
		using dim_t = decltype(r);
		using value_type = type;
		using properties = template_traits::vectorial_properties<r>;

	public:
		constexpr size_t rank() const noexcept { return 1; }
		constexpr size_t size() const noexcept { return r; }
		constexpr size_t dimention() const noexcept { return r; }

		constexpr double fastMagnitude() const noexcept {
			type acumulator{};

			for (size_t i = 0; i < r; i++) {
				acumulator += buffer[i] * buffer[i];
			}
			return acumulator;

			// // ((acumulator += buffer[r-1] * buffer[r - 1]), ...);  // fold expression
			return static_cast<double>(acumulator);
		}
		constexpr double norm() const noexcept {
			return sqrt(this->fastMagnitude());
		}

		constexpr value_type dotProduct(vector) const noexcept;

		constexpr vector &normalize() noexcept;
		constexpr vector &hadamardProduct(vector);
		constexpr vector &crossProduct(vector);

		constexpr matrix<value_type, r, r> outerProduct(vector);

		constexpr vector &operator+(vector other) noexcept {}
		constexpr vector &operator-(vector other) noexcept {}
		constexpr vector &operator*(vector other) noexcept {}
		constexpr vector &operator/(vector other) noexcept {}

		constexpr vector &operator+(require::Real auto scalar) noexcept {}
		constexpr vector &operator-(require::Real auto scalar) noexcept {}
		constexpr vector &operator*(require::Real auto scalar) noexcept {}
		constexpr vector &operator/(require::Real auto scalar) noexcept {}


		constexpr value_type &operator[](require::Integral auto index) noexcept {
		}
		constexpr const value_type &operator[](require::Integral auto index) const noexcept {
		}

		// >Shady practices incomming

		

	public:
		// type buffer[r] = {};
		std::array<value_type, r> buffer = {};
		
	};


	
}