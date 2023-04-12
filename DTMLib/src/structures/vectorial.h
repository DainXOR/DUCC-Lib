#pragma once

#include <array>
#include <vector>
#include <math.h>

#include "../utilities/constrains.h"
#include "../functions/arithmetic.h"

#include <macro_tools.h>

namespace duc{

	template<require::Complex type = float, require::Integer auto r = 0>
	class vector;

	template<require::Complex type = float, require::Integer auto m = 3, require::Integer auto n = 3>
	class matrix;

	template<require::Complex type = float, require::Integer auto... dims>
	class tensor;



	template<require::Complex type, require::Integer auto r>
	class vector {
	public:
		using dim_t = decltype(r);
		using properties = math_utils::vectorial_properties<r>;

		using buffer_type = std::conditional_t< r && (r < (((1 << 6) - 1) / sizeof(type))),
			std::array<type, r>, 
			std::vector<type>>;



		buffer_type buffer = { 0 };

	public:
		constexpr size_t rank()			DUC_CONST_RNOEXCEPT { return 1; }
		constexpr size_t size()			DUC_CONST_RNOEXCEPT { return r; }
		constexpr size_t dimention()	DUC_CONST_RNOEXCEPT { return this->size(); }

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
		constexpr double fastNorm() const noexcept {
			return fastInvSqrt(this->fastMagnitude());
		}

		constexpr type dotProduct(const require::Vector auto& other) DUC_CONST_RNOEXCEPT {
			DUC_TEST_ERROR(this->size() == other.size(), std::invalid_argument, "The vectors must have the same size.");

			type result = 0;
			for (int i = 0; i < this->size(); i++) {
				result += buffer[i] * other[i];
			}

			return result;
		}

		constexpr vector& normalize() DUC_RNOEXCEPT {
			return *this /= norm();
		}
		constexpr vector& fastNormalize() DUC_RNOEXCEPT {
			return *this /= fastNorm();
		}

		constexpr vector& hadamardProduct(const require::Vector auto& other);
		constexpr vector& crossProduct(const require::Vector auto& other);

		constexpr matrix<type, r, r> outerProduct(const require::Vector auto& other) const ;

		template<typename other_type>
		constexpr vector<type, r> operator+(const vector<other_type, r>& other) DUC_CONST_RNOEXCEPT {
			DUC_TEST_ERROR(size() == other.size(), std::invalid_argument, "The vectors must have the same size.");
			
			vector<type, r> result;
			for (int i = 0; i < this->size(); i++) {
				result[i] = buffer[i] + type(other[i]);
			}
			return result;
		}
		template<typename other_type>
		constexpr vector<type, r> operator-(const vector<other_type, r>& other) DUC_CONST_RNOEXCEPT {
			DUC_TEST_ERROR(size() == other.size(), std::invalid_argument, "The vectors must have the same size.");
			
			vector<type, r> result;
			for (int i = 0; i < this->size(); i++) {
				result[i] = buffer[i] - type(other[i]);
			}
			return result;
		}
		template<typename other_type>
		constexpr vector<type, r> operator*(const vector<other_type, r>& other) DUC_CONST_RNOEXCEPT {
			DUC_TEST_ERROR(size() == other.size(), std::invalid_argument, "The vectors must have the same size.");

			vector<type, r> result;
			for (int i = 0; i < this->size(); i++) {
				result[i] = buffer[i] * type(other[i]);
			}
			return result;
		}
		template<typename other_type>
		constexpr vector<type, r> operator/(const vector<other_type, r>& other) DUC_CONST_RNOEXCEPT {
			DUC_TEST_ERROR(size() == other.size(), std::invalid_argument, "The vectors must have the same size.");

			vector<type, r> result;
			for (int i = 0; i < this->size(); i++) {
				result[i] = buffer[i] / type(other[i]);
			}
			return result;
		}

		constexpr vector<type, r> operator+(require::Real auto scalar) DUC_CONST_RNOEXCEPT {
			vector<type, r> result;
			for (int i = 0; i < size(); i++) {
				result[i] = buffer[i] + scalar;
			}
			return result;
		}
		constexpr vector<type, r> operator-(require::Real auto scalar) DUC_CONST_RNOEXCEPT {
			vector<type, r> result;
			for (int i = 0; i < size(); i++) {
				result[i] = buffer[i] - scalar;
			}
			return result;
		}
		constexpr vector<type, r> operator*(require::Real auto scalar) DUC_CONST_RNOEXCEPT {
			vector<type, r> result;
			for (int i = 0; i < size(); i++) {
				result[i] = buffer[i] * scalar;
			}
			return result;
		}
		constexpr vector<type, r> operator/(require::Real auto scalar) DUC_CONST_RNOEXCEPT {
			vector<type, r> result;
			for (int i = 0; i < size(); i++) {
				result[i] = buffer[i] / scalar;
			}
			return result;
		}

		template<typename other_type>
		constexpr vector<type, r>& operator+=(const vector<other_type, r>& other) DUC_RNOEXCEPT {
			*this = (*this) + other;
			return *this;
		}
		template<typename other_type>
		constexpr vector<type, r>& operator-=(const vector<other_type, r>& other) DUC_RNOEXCEPT {
			*this = (*this) - other;
			return *this;
		}
		template<typename other_type>
		constexpr vector<type, r>& operator*=(const vector<other_type, r>& other) DUC_RNOEXCEPT {
			*this = (*this) * other;
			return *this;
		}
		template<typename other_type>
		constexpr vector<type, r>& operator/=(const vector<other_type, r>& other) DUC_RNOEXCEPT {
			*this = (*this) / other;
			return *this;
		}

		constexpr vector<type, r>& operator+=(require::Real auto scalar) DUC_RNOEXCEPT {
			*this = (*this) + scalar;
			return *this;
		}
		constexpr vector<type, r>& operator-=(require::Real auto scalar) DUC_RNOEXCEPT {
			*this = (*this) - scalar;
			return *this;
		}
		constexpr vector<type, r>& operator*=(require::Real auto scalar) DUC_RNOEXCEPT {
			*this = (*this) * scalar;
			return *this;
		}
		constexpr vector<type, r>& operator/=(require::Real auto scalar) DUC_RNOEXCEPT {
			*this = (*this) / scalar;
			return *this;
		}

		constexpr vector<type, r> operator-() DUC_RNOEXCEPT {
			return (*this) - ((*this) * 2);
		}


		constexpr type &operator[](const require::Integer auto& index) DUC_RNOEXCEPT {
			DUC_TEST_ERROR(index < size(), std::out_of_range, "Index out of bounds.");

			return buffer[index];
		}
		constexpr const type& operator[](const require::Integer auto& index) DUC_CONST_RNOEXCEPT {
			DUC_TEST_ERROR(index < size(), std::out_of_range, "Index out of bounds.");

			return buffer[index];
		}

		constexpr type& at(const require::Integer auto& index) {
			if (index >= size())
				throw std::out_of_range("Index out of bounds.");

			if (index < 0 && duc::abs(index) < size() - 1)
				return buffer.at(this->size() - index);

			return buffer.at(index);
		}
		auto front() {
			return this->buffer.front();
		}
		auto back() {
			return this->buffer.back();
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

		auto cbegin() {
			return this->buffer.cbegin();
		}
		auto cend() {
			return this->buffer.cend();
		}

		auto crbegin() {
			return this->buffer.crbegin();
		}
		auto crend() {
			return this->buffer.crend();
		}


		// >Shady practices incomming

		
		
	};

	template<require::Complex type, require::Integer auto m, require::Integer auto n>
	class matrix {
	};

	template<require::Complex type, require::Integer auto... dims>
	class tensor {

		using dim_t = std::common_type_t<decltype(dims)...>;
		using properties = math_utils::vectorial_properties<dims...>;

		/*template<uint16_t _size>
		using iterator = std::_Array_iterator<type, _size>;
		template<uint16_t _size>
		using const_iterator = std::_Array_const_iterator<type, _size>;

		template<class iter>
		using reverse_iterator = std::reverse_iterator<iter>;
		template<class const_iter>
		using const_reverse_iterator = std::reverse_iterator<const_iter>;*/

		// std::vector<type> mp_buffer = std::vector<type>(tp::size);

		using buffer_type = std::conditional_t< properties::rank && (properties::size < (((1ull << 32ull) - 1) / sizeof(type))),
			std::array<type, properties::size>,
			std::vector<type>>;

		buffer_type buffer = { 0 };

	public:
		// > Properties methods

		constexpr size_t size()	DUC_CONST_RNOEXCEPT		{ return properties::size; }
		constexpr uint16_t rank() DUC_CONST_RNOEXCEPT	{ return properties::rank; }
		constexpr auto shape() DUC_CONST_RNOEXCEPT		{ return properties::shape; }
		constexpr size_t dimention(const require::Integer auto& rankPos) DUC_CONST_RNOEXCEPT {
			DUC_TEST_ERROR((rankPos > properties::rank) || (rankPos < 0), std::out_of_range, "Rank outside tensor.\n");

			return properties::shape[rankPos];
		}

		// > Access functions and operators

		constexpr type& operator [](size_t index) DUC_RNOEXCEPT {
			DUC_TEST_ERROR(index >= size(), std::out_of_range, "The index is outside the tensor. (Max = " + duc::toChars(size() - 1) + ")");

			return buffer[index];
		}
		[[nodiscard]] constexpr const type& operator [](size_t index) DUC_CONST_RNOEXCEPT {
			DUC_TEST_ERROR(index < size(), std::out_of_range, "The index is outside the tensor. (Max = " + duc::toChars(size() - 1) + ")");

			return buffer[index];
		}

		constexpr type& operator()(require::Integer auto... indexes) DUC_RNOEXCEPT {

			constexpr uint16_t IndexCount = sizeof...(indexes);
			DUC_TEST_ERROR(IndexCount, std::invalid_argument, "No indexes provided.");
			DUC_TEST_ERROR(IndexCount <= rank(), std::out_of_range, "Amount of indexes provided exceed the tensor rank.");

			constexpr std::array<size_t, IndexCount> IndexesArray = { indexes... };
			constexpr std::array Multipliers = math_utils::calculateMultipliers(shape());
			size_t index = 0;

			for (uint16_t i = 0; i <= rank(); i++) {
				DUC_TEST_ERROR(IndexesArray[i] < 0, std::invalid_argument, "Negative indexes are not allowed.");
				DUC_TEST_ERROR(IndexesArray[i] < dimention(i), std::out_of_range, "The index is outside the tensor.\n(Max =" + duc::toChars(dimention(i) - 1) + ", Attempted[" + duc::toChars(IndexesArray[i]) + "])");

				index += IndexesArray[i] * Multipliers[i];
			}

			return buffer[index];

		}

		/*
		constexpr std::optional<const reference> operator ()(constrains::UnsignedIntegral auto... indexes){

			constexpr uint16_t IndexCount = sizeof...(indexes);
			if (!IndexCount) {
				return std::nullopt;
			}

			if (IndexCount > rank()) {
				return std::nullopt;
			}

			std::array<size_t, IndexCount> IndexesArray = { indexes... };

			for (size_t i = 0; i < IndexCount; ++i) {
				if (IndexesArray[i] >= dimention(i)) {
					return std::nullopt;
				}
			}

			constexpr std::array Multipliers = multipliers(dimentions());

			size_t index = 0;
			for (size_t i = 0; i < IndexCount; ++i) {
				index += IndexesArray[i] * Multipliers[i];
			}

			return mp_buffer[index];
		}
		*/

		// > Math operations functions and operators
		tensor& operator+(const tensor& other) DUC_RNOEXCEPT {
			DUC_TEST_ERROR(math_utils::isTensorsShapeCompatible(rank(), shape(), other.shape()),
						   std::invalid_argument,
						   "The tensors must have a compatible shape.");

			for (size_t i = 0; i < this->size(); i++) {
				buffer[i] += other[i];
			}

			// Do Einstain Summation

			return this;
		}
		tensor& operator+(require::Real auto scalar) {
			for (size_t i = 0; i < this->size(); i++) {
				buffer[i] += scalar;
			}
			return this;
		}

		tensor& operator-(const tensor& other) {
			DUC_TEST_ERROR(math_utils::isTensorsShapeCompatible(rank(), shape(), other.shape()),
						   std::invalid_argument,
						   "The tensors must have a compatible shape."
			);

			for (size_t i = 0; i < this->size(); i++) {
				buffer[i] -= other[i];
			}

			// Do Einstain Summation

			return this;
		}
		tensor& operator-(require::Real auto scalar) {
			for (size_t i = 0; i < this->size(); i++) {
				buffer[i] -= scalar;
			}
			return this;
		}

	private:

		template<require::UnsignedInteger... size_type = size_t>
		std::enable_if<properties::rank != 0> changeDims(size_type... dims) {

		}

	};

	
}