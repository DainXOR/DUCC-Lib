#pragma once

#include <array>
#include <vector>
#include <math.h>

#include "../utilities/constrains.h"

namespace duc{

	template<require::Complex type = float, require::Integral auto r = 0>
	class vector;

	template<require::Complex type, require::Integral auto m, require::Integral auto n>
	class matrix;

	template<require::Complex type, require::Integral auto... dims>
	class tensor;



	template<require::Complex type = float, require::Integral auto r = 0>
	class vector {
	public:
		using dim_t = decltype(r);
		using value_type = type;
		using properties = math_utils::vectorial_properties<r>;

		// std::array<type, r> buffer = {};
		// std::conditional_t<r && (r < (((1 << 16) - 1) / sizeof(value_type))),
		std::conditional_t<
			r && (r < (((1 << 6) - 1) / sizeof(type))),
			std::array<type, r>, std::vector<type>> buffer = {0};

	public:
		constexpr size_t rank() const noexcept { return 1; }
		constexpr size_t size() const noexcept { return r; }
		constexpr size_t dimention() const noexcept { return this->size(); }

		constexpr double fastMagnitude() const noexcept {
			type acumulator{};

			for (size_t i = 0; i < r; i++) {
				acumulator += this->buffer[i] * this->buffer[i];
			}
			return acumulator;

			// // ((acumulator += buffer[r-1] * buffer[r - 1]), ...);  // fold expression
			return static_cast<double>(acumulator);
		}
		constexpr double norm() const noexcept {
			return sqrt(this->fastMagnitude());
		}

		constexpr value_type dotProduct(const require::Vector auto& other) const noexcept;

		constexpr vector& normalize() noexcept;
		constexpr vector& hadamardProduct(const require::Vector auto& other);
		constexpr vector& crossProduct(const require::Vector auto& other);

		constexpr matrix<value_type, r, r> outerProduct(const require::Vector auto& other) const ;

		constexpr vector &operator+(const require::Vector auto& other) noexcept {}
		constexpr vector &operator-(const require::Vector auto& other) noexcept {}
		constexpr vector &operator*(const require::Vector auto& other) noexcept {}
		constexpr vector &operator/(const require::Vector auto& other) noexcept {}

		constexpr vector &operator+(const require::Real auto& scalar) noexcept {}
		constexpr vector &operator-(const require::Real auto& scalar) noexcept {}
		constexpr vector &operator*(const require::Real auto& scalar) noexcept {}
		constexpr vector &operator/(const require::Real auto& scalar) noexcept {}


		constexpr value_type &operator[](const require::Integral auto& index) noexcept {
			#ifndef NDEBUG
			(index >= this->size());
			#endif
		}
		constexpr const value_type &operator[](const require::Integral auto& index) const noexcept {

		}

		auto begin() {
			return this->buffer.begin();
		}
		auto end() {
			return this->buffer.end();
		}

		auto rbegin() {
			return this->buffer.rbegin();
		}
		auto rend() {
			return this->buffer.rend();
		}

		// >Shady practices incomming

		
		
	};


	
}