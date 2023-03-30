#pragma once

#include "../utilities/constrains.h"

namespace duc{
	using namespace math_utils;

	template<require::Arithmetic type, require::Integral auto m, require::Integral auto n>
	class matrix;

	template<require::UnsignedIntegral auto r, require::Arithmetic type>
	class vector {
	public:
		using dim_t = decltype(r);
		using properties = template_traits::vectorial_properties<r>;

	public:
		constexpr size_t rank() { return 1; }
		constexpr size_t size() { return r; }
		constexpr size_t dimention() { return r; }

		constexpr size_t magnitude() {
			type acumulator = 0;

			for (dim_t i = r - 1; i >= 0; i--) {
				acumulator += buffer[i] * buffer[i];
			}
			return acumulator;
		}
		constexpr size_t norm() {
			type acumulator = 0;

			for (dim_t i = r - 1; i >= 0; i--) {
				acumulator = buffer[i] * buffer[i];
			}
			return acumulator;
		}

		type dotProduct(vector);

		vector &hadamardProduct(vector);
		vector &crossProduct(vector);
		vector &normalize();

		matrix<type, r, r> outerProduct(vector);
		
		vector &operator+(vector other) {}
		vector &operator-(vector other) {}
		vector &operator*(vector other) {}
		vector &operator/(vector other) {}

		template<require::Decimal scalar_t>
		vector &operator+(scalar_t scalar){}

		template<require::Decimal scalar_t>
		vector &operator-(scalar_t scalar){}

		template<require::Decimal scalar_t>
		vector &operator*(scalar_t scalar){}

		template<require::Decimal scalar_t>
		vector &operator/(scalar_t scalar){}


		type &operator[](require::Integral auto index);

		// >Shady practices incomming

		using buffer_type = type;

	public:
		type buffer[r] = {};
		//std::array<type, r> buffer = {};
		
	};


	
}