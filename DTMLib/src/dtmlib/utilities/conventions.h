#pragma once
#include <type_traits>

#include <cudlib/general_conventions.h>

#include "template_traits.h"

/// \Todo Rename file to conventions

// > condition | convention | standard | satisfy 
namespace duc::satisfy { 

	/// > General Math Concepts

	template<typename value_type>
	concept Integer = std::_Is_nonbool_integral<value_type>; // std::is_integral_v<value_type> && !std::is_same_v<std::remove_cv_t<value_type>, bool>;

	template<typename value_type>
	concept UnsignedInteger = Integer<value_type> && std::is_unsigned_v<value_type>;

	template<typename value_type>
	concept Decimal = std::is_floating_point_v<value_type>;

	template<typename value_type>
	concept Real = Integer<value_type> || Decimal<value_type>;

	template<typename value_type>
	concept Arithmetic = Real<value_type> || requires(value_type A, value_type B, double C) {
			{ A + B }; // -> std::convertible_to<value_type>;
			{ A - B }; // -> std::convertible_to<value_type>;
			{ A * B }; // -> std::convertible_to<value_type>;
			{ A / B }; // -> std::convertible_to<value_type>;

			{ A + C }; // -> std::convertible_to<value_type>;
			{ A - C }; // -> std::convertible_to<value_type>;
			{ A * C }; // -> std::convertible_to<value_type>;
			{ A / C }; // -> std::convertible_to<value_type>;

			{ A <=> B }; // -> std::convertible_to<value_type>;
			{ A <=> C }; // -> std::convertible_to<value_type>;
		};

	template<typename value_type>
	concept Complex = requires(value_type A, double C) {
		Real<value_type> || Arithmetic<value_type>;

		{ A + C } -> std::convertible_to<value_type>;
		{ A - C } -> std::convertible_to<value_type>;
		{ A * C } -> std::convertible_to<value_type>;
		{ A / C } -> std::convertible_to<value_type>;

		// A = double();
	};

	template<typename value_type>
	concept StrictComplex = requires (value_type A) {
		Complex<value_type>;
		A.real();
		A.imag();
	};



	/// > Vectorial Concepts

	template<class tensor_t>
	concept Tensor = requires (tensor_t T1, tensor_t T2, double S, int64_t I) {
		T1.rank() > 0;
		T1.shape();

		{ T1 + T2 }; // -> std::convertible_to<value_type>;
		{ T1 - T2 }; // -> std::convertible_to<value_type>;
		{ T1 * T2 }; // -> std::convertible_to<value_type>;

		{ T1 + S }; // -> std::convertible_to<value_type>;
		{ T1 - S }; // -> std::convertible_to<value_type>;
		{ T1 * S }; // -> std::convertible_to<value_type>;
		{ T1 / S }; // -> std::convertible_to<value_type>;

		{ -T1 };

		T1[I];
	};
	template<class matrix_t>
	concept Matrix = requires(matrix_t M1) {
		Tensor<matrix_t>;

		M1.rank() == 2;
	};
	template<class vector_t>
	concept Vector = requires(vector_t V1, vector_t V2) {
		Tensor<vector_t>;

		V1.rank() == 1;

		V1.norm();
		V1.normalize();
		V1.crossProduct(V2);
		V1.dotProduct(V2);

	};

	template<typename space_t>
	concept VectorialSpace = requires(space_t S1) {
		S1.innerProduct();
	};

	template<typename value_type>
	concept Vectorial = Vector<value_type> || Matrix<value_type> || Tensor<value_type> || VectorialSpace<value_type>;

	template<typename value_type>
	concept VectorialProperties = requires {
		Integer<decltype(value_type::size)>;
		Integer<decltype(value_type::rank)>;
		Indexable<decltype(value_type::shape)>;
	};

}

	
