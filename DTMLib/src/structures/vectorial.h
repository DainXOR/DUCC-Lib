#pragma once

#include <array>
//#include <vector>

#include "../utilities/conventions.h"
#include "../functions/arithmetic.h"

#include <general_utils.h>
#include <general_conventions.h>
#include <macro_tools.h>

namespace duc{
	using namespace satisfy;
	/// > Declarations

	template<satisfy::Integer auto r = 2, satisfy::Complex type = float,
		template<typename, size_t> class container = std::array>
		requires satisfy::Container<container<type, r>>
	class vector;

	template<satisfy::Integer auto m = 3, satisfy::Integer auto n = 3, satisfy::Complex type = float,
		template<typename, size_t> class container = std::array>
	class matrix;

	template<satisfy::VectorialProperties properties = trait::vectorial<3, 3, 3>, satisfy::Complex type = float,
		template<typename, size_t> class container = std::array>
	class tensor;


	/// > Definitions

	template<satisfy::Integer auto r, satisfy::Complex type, template<typename, size_t> class container>
		requires satisfy::Container<container<type, r>>
	class vector {
	public:
		DUC_SATISFIES(r > 0, "Vector size must be greater than cero.");

		using traits = trait::vectorial<r>;
		using value_type = type;
		using buffer_type = container<type, r>;

		using iterator = buffer_type::iterator;
		using const_iterator = buffer_type::const_iterator;

		using reverse_iterator = buffer_type::reverse_iterator;
		using const_reverse_iterator = buffer_type::const_reverse_iterator;

		buffer_type _elements = { 0 };

	public:
		constexpr int64_t rank()			DUC_CONST_RNOEXCEPT { return 1; }
		constexpr int64_t size()			DUC_CONST_RNOEXCEPT { return r; }
		constexpr int64_t max_size()		DUC_CONST_RNOEXCEPT { return r; }
		constexpr int64_t shape()			DUC_CONST_RNOEXCEPT { return r; }
		constexpr int64_t dimention(size_t)	DUC_CONST_RNOEXCEPT { return r; }
		constexpr bool	  empty()			DUC_CONST_RNOEXCEPT { return false; }

		//constexpr vector& operator=(const satisfy::Vector auto& other) DUC_RNOEXCEPT {
		//	//DUC_TEST_ERROR((std::convertible_to<other_type, type>), std::invalid_argument, duc::util::concat(
		//	//	"Type ", typeid(other_type).name(), " cannot be converted into ", typeid(type).name(), "."));
		//
		//	(&other != this) && std::copy(other.begin(), other.end(), this->begin());
		//	return *this;
		//}

		constexpr vector operator+(const auto& other) DUC_CONST_RNOEXCEPT {
			DUC_TEST_THROW(this->size() == other.size(), "The vectors must have the same size.");

			vector result = (*this);
			vector other_vector = other;

			for (int i = 0; i < this->size(); i++) {
				result[i] += other_vector[i];
			}
			return result;
		}
		constexpr vector operator-(const auto& other) DUC_CONST_RNOEXCEPT {
			DUC_TEST_ERROR(this->size() == other.size(), "The vectors must have the same size.");


			vector result = (*this);
			vector other_vector = other;

			for (int i = 0; i < this->size(); i++) {
				result[i] -= other_vector[i];
			}
			return result;
		}
		constexpr vector operator*(const auto& other) DUC_CONST_RNOEXCEPT {
			DUC_TEST_ERROR(this->size() == other.size(), "The vectors must have the same size.");

			vector result = (*this);
			vector other_vector = other;

			for (int i = 0; i < this->size(); i++) {
				result[i] *= other_vector[i];
			}
			return result;
		}
		constexpr vector operator/(const auto& other) DUC_CONST_RNOEXCEPT {
			DUC_TEST_ERROR(this->size() == other.size(), "The vectors must have the same size.");

			vector result = (*this);
			vector other_vector = other;

			for (int i = 0; i < this->size(); i++) {
				result[i] /= other_vector[i];
			}
			return result;
		}

		constexpr vector operator+(type scalar) DUC_CONST_RNOEXCEPT {
			vector result = (*this);

			for (int i = 0; i < size(); i++) {
				result[i] += scalar;
			}
			return result;
		}
		constexpr vector operator-(type scalar) DUC_CONST_RNOEXCEPT {
			vector result = (*this);

			for (int i = 0; i < size(); i++) {
				result[i] -= scalar;
			}
			return result;
		}
		constexpr vector operator*(type scalar) DUC_CONST_RNOEXCEPT {
			vector result = (*this);

			for (int i = 0; i < size(); i++) {
				result[i] *= scalar;
			}
			return result;
		}
		constexpr vector operator/(type scalar) DUC_CONST_RNOEXCEPT {
			vector result = (*this);

			for (int i = 0; i < size(); i++) {
				result[i] /= scalar;
			}
			return result;
		}

		constexpr vector& operator+=(const auto& other) DUC_RNOEXCEPT {
			(*this) = (*this) + other;
			return *this;
		}
		constexpr vector& operator-=(const auto& other) DUC_RNOEXCEPT {
			*this = (*this) - other;
			return *this;
		}
		constexpr vector& operator*=(const auto& other) DUC_RNOEXCEPT {
			*this = (*this) * other;
			return *this;
		}
		constexpr vector& operator/=(const auto& other) DUC_RNOEXCEPT {
			*this = (*this) / other;
			return *this;
		}

		constexpr vector<r, type, container> operator-() DUC_RNOEXCEPT {
			return (*this) * -1;
		}

		template<std::convertible_to<type> other_type, template<typename, size_t> class other_container>
		constexpr std::strong_ordering operator<=>(const vector<r, other_type, other_container>& other) {
			return this->fastMagnitude() <=> other.fastMagnitude();
		}

		constexpr double fastMagnitude() DUC_CONST_RNOEXCEPT {
			type acumulator{};

			for (size_t i = 0; i < r; i++) {
				acumulator += this->_elements[i] * this->_elements[i];
			}
			// // ((acumulator += _elements[r-1] * _elements[r - 1]), ...);  // fold expression
			return static_cast<double>(acumulator);
		}
		constexpr double norm() DUC_CONST_RNOEXCEPT {
			return duc::root(this->fastMagnitude(), 2);
		}

		constexpr vector& normalize() DUC_RNOEXCEPT {
			return (*this) /= norm();
		}
		constexpr vector& fastNormalize() DUC_RNOEXCEPT {
			return (*this) *= duc::fastInvSqrt(float(fastMagnitude()));
		}

		template<typename vector_t>
		constexpr double angle(const vector_t& other) DUC_CONST_RNOEXCEPT {
			return this->dotProduct(other) / (this->norm() * other.norm());
		}

		constexpr type dotProduct(const auto& other) DUC_CONST_RNOEXCEPT {
			DUC_TEST_ERROR(this->size() == other.size(), "The vectors must have the same size.");

			type result = 0;
			for (int i = 0; i < this->size(); i++) {
				result += _elements[i] * other[i];
			}

			return result;
		}

		constexpr vector& hadamardProduct(const satisfy::Vector auto& other) DUC_RNOEXCEPT {
			return (*this);
		}
		template<typename vector_t>
		constexpr vector& crossProduct(const vector_t& other) DUC_RNOEXCEPT {
			return (*this);
		}

		constexpr matrix<r, r, type> outerProduct(const satisfy::Vector auto& other) DUC_CONST_RNOEXCEPT {
			return (*this);
		}

		
		// > Indexing

		constexpr type &operator[](const satisfy::Integer auto& index) DUC_RNOEXCEPT {
			DUC_TEST_THROW(index < size() && index >= 0, "Index out of bounds.");

			return _elements[index];
		}
		constexpr const type& operator[](const satisfy::Integer auto& index) DUC_CONST_RNOEXCEPT {
			return _elements[index];
		}

		constexpr type& at(satisfy::Integer auto index) {
			if (index >= signed(size()) || duc::abs(index) > size())
				throw std::out_of_range("Index out of bounds.");

			
			if (index < 0)
				return _elements[size() + index];

			return _elements[index];
		}
		constexpr const type& at(satisfy::Integer auto index) const {
			return this->at(index);
		}
		
		constexpr auto& front() DUC_RNOEXCEPT {
			return this->at(0);
		}
		constexpr auto& back() DUC_RNOEXCEPT {
			return this->at(-1);
		}

		// > Iterators

		constexpr iterator begin() DUC_RNOEXCEPT requires(satisfy::Iterable<buffer_type>) {
			return std::begin(_elements);
		}
		constexpr iterator end() DUC_RNOEXCEPT requires(satisfy::Iterable<buffer_type>) {
			return std::end(_elements);
		}

		constexpr reverse_iterator rbegin() DUC_RNOEXCEPT requires(satisfy::Iterable<buffer_type>) {
			return std::rbegin(_elements);
		}
		constexpr reverse_iterator rend() DUC_RNOEXCEPT requires(satisfy::Iterable<buffer_type>) {
			return std::rend(_elements);
		}

		constexpr const_iterator cbegin() DUC_CONST_RNOEXCEPT requires(satisfy::Iterable<buffer_type>) {
			return std::cbegin(_elements);
		}
		constexpr const_iterator cend() DUC_CONST_RNOEXCEPT requires(satisfy::Iterable<buffer_type>) {
			return std::cend(_elements);
		}

		constexpr const_reverse_iterator crbegin() DUC_CONST_RNOEXCEPT requires(satisfy::Iterable<buffer_type>) {
			return std::crbegin(_elements);
		}
		constexpr const_reverse_iterator crend() DUC_CONST_RNOEXCEPT requires(satisfy::Iterable<buffer_type>) {
			return std::crend(_elements);
		}
		
		constexpr void swap(satisfy::Vector auto& other) {
			std::swap(this->_elements, other._elements);
		}

		// > Convertion operators
		operator bool() DUC_CONST_RNOEXCEPT { return bool(fastMagnitude()); }
	};

	//template<satisfy::Integer auto r, typename type, template<typename, size_t> class container>
	//class vector<r, type, container> {
	//	
	//};

	template<satisfy::Integer auto m, satisfy::Integer auto n, satisfy::Complex type, template<typename, size_t> class container>
	class matrix {
	public:
		DUC_SATISFIES(m * n > 0, "Matrix size must be greater than cero.");

		using traits = trait::vectorial<m, n>;
		using value_type = type;
		using buffer_type = container<type, m * n>;

		buffer_type _elements = { 0 };

	public:
		constexpr int64_t	rank()					DUC_CONST_RNOEXCEPT { return 1; }
		constexpr int64_t	size()					DUC_CONST_RNOEXCEPT { return traits::size; }
		constexpr int64_t	max_size()				DUC_CONST_RNOEXCEPT { return traits::size; }
		constexpr auto		shape()					DUC_CONST_RNOEXCEPT { return traits::shape; }
		constexpr int64_t	dimention(size_t dim)	DUC_CONST_RNOEXCEPT { return shape()[dim]; }
		constexpr bool		empty()					DUC_CONST_RNOEXCEPT { return false; }


		constexpr matrix operator+(const auto& other) DUC_CONST_RNOEXCEPT {
			DUC_TEST_THROW(this->size() == other.size(), "The vectors must have the same size.");

			matrix result = (*this);
			matrix other_matrix = other;

			for (int i = 0; i < this->size(); i++) {
				result[i] += other_matrix[i];
			}
			return result;
		}
		constexpr matrix operator-(const auto& other) DUC_CONST_RNOEXCEPT {
			DUC_TEST_ERROR(this->size() == other.size(), "The vectors must have the same size.");


			matrix result = (*this);
			matrix other_matrix = other;

			for (int i = 0; i < this->size(); i++) {
				result[i] -= other_matrix[i];
			}
			return result;
		}
		constexpr matrix operator*(const auto& other) DUC_CONST_RNOEXCEPT {
			DUC_TEST_ERROR(this->size() == other.size(), "The vectors must have the same size.");

			matrix result = (*this);
			matrix other_matrix = other;

			for (int i = 0; i < this->size(); i++) {
				result[i] *= other_matrix[i];
			}
			return result;
		}
		constexpr matrix operator/(const auto& other) DUC_CONST_RNOEXCEPT {
			DUC_TEST_ERROR(this->size() == other.size(), "The vectors must have the same size.");

			matrix result = (*this);
			matrix other_matrix = other;

			for (int i = 0; i < this->size(); i++) {
				result[i] /= other_matrix[i];
			}
			return result;
		}

		constexpr matrix operator+(type scalar) DUC_CONST_RNOEXCEPT {
			matrix result = (*this);

			for (int i = 0; i < size(); i++) {
				result[i] += scalar;
			}
			return result;
		}
		constexpr matrix operator-(type scalar) DUC_CONST_RNOEXCEPT {
			matrix result = (*this);

			for (int i = 0; i < size(); i++) {
				result[i] -= scalar;
			}
			return result;
		}
		constexpr matrix operator*(type scalar) DUC_CONST_RNOEXCEPT {
			matrix result = (*this);

			for (int i = 0; i < size(); i++) {
				result[i] *= scalar;
			}
			return result;
		}
		constexpr matrix operator/(type scalar) DUC_CONST_RNOEXCEPT {
			matrix result = (*this);

			for (int i = 0; i < size(); i++) {
				result[i] /= scalar;
			}
			return result;
		}

		constexpr matrix& operator+=(const auto& other) DUC_RNOEXCEPT {
			(*this) = (*this) + other;
			return *this;
		}
		constexpr matrix& operator-=(const auto& other) DUC_RNOEXCEPT {
			*this = (*this) - other;
			return *this;
		}
		constexpr matrix& operator*=(const auto& other) DUC_RNOEXCEPT {
			*this = (*this) * other;
			return *this;
		}
		constexpr matrix& operator/=(const auto& other) DUC_RNOEXCEPT {
			*this = (*this) / other;
			return *this;
		}

		constexpr matrix& operator-() DUC_RNOEXCEPT {
			return (*this) * -1;
		}

		template<std::convertible_to<type> other_type, template<typename, size_t> class other_container>
		constexpr std::strong_ordering operator<=>(const matrix<m, n, other_type, other_container>& other) {
			return this->size() <=> other.size();
		}



		// > Indexing

		constexpr type &operator[](const satisfy::Integer auto& index) DUC_RNOEXCEPT {
			DUC_TEST_THROW(index < size() && index >= 0, "Index out of bounds.");

			return _elements[index];
		}
		constexpr const type& operator[](const satisfy::Integer auto& index) DUC_CONST_RNOEXCEPT {
			return _elements[index];
		}

		constexpr type& at(satisfy::Integer auto index) {
			if (index >= signed(size()) || duc::abs(index) > size())
				throw std::out_of_range("Index out of bounds.");


			if (index < 0)
				return _elements[size() + index];

			return _elements[index];
		}
		constexpr const type& at(satisfy::Integer auto index) const {
			if (index >= signed(size()) || duc::abs(index) > size())
				throw std::out_of_range("Index out of bounds.");


			if (index < 0)
				return _elements[size() + index];

			return _elements[index];
		}

		constexpr auto& front() {
			return this->at(0);
		}
		constexpr auto& back() {
			return this->at(-1);
		}

		// > Iterators

		template<typename = std::enable_if_t<satisfy::Iterable<buffer_type>>>
		constexpr auto begin() {
			return std::begin(_elements);
		}
		template<typename = std::enable_if_t<satisfy::Iterable<buffer_type>>>
		constexpr auto end() {
			return std::end(_elements);
		}

		template<typename = std::enable_if_t<satisfy::Iterable<buffer_type>>>
		constexpr auto rbegin() {
			return std::rbegin(_elements);
		}
		template<typename = std::enable_if_t<satisfy::Iterable<buffer_type>>>
		constexpr auto rend() {
			return std::rend(_elements);
		}

		template<typename = std::enable_if_t<satisfy::Iterable<buffer_type>>>
		constexpr auto cbegin() {
			return std::cbegin(_elements);
		}
		template<typename = std::enable_if_t<satisfy::Iterable<buffer_type>>>
		constexpr auto cend() {
			return std::cend(_elements);
		}

		template<typename = std::enable_if_t<satisfy::Iterable<buffer_type>>>
		constexpr auto crbegin() {
			return std::crbegin(_elements);
		}
		template<typename = std::enable_if_t<satisfy::Iterable<buffer_type>>>
		constexpr auto crend() {
			return std::crend(_elements);
		}

		template<std::convertible_to<type> other_type, template<typename, size_t> class other_container>
		constexpr void swap(matrix<m, n, other_type, other_container>& other) {
			std::swap(this->_elements, other._elements);
		}



	};

	template<satisfy::VectorialProperties properties, satisfy::Complex type, template<typename, size_t> class container>
	class tensor {

		DUC_SATISFIES(properties::size > 0, "Tensor size must be greater than cero.");

		using dim_t = uint16_t;
		using traits = properties;
		using value_type = type;
		using buffer_type = container<type,traits::size>;

		buffer_type _elements = { 0 };

	public:
		// > Properties methods

		constexpr size_t	size()	DUC_CONST_RNOEXCEPT		{ return traits::size; }
		constexpr uint16_t	rank() DUC_CONST_RNOEXCEPT	{ return traits::rank; }
		constexpr auto		shape() DUC_CONST_RNOEXCEPT		{ return traits::shape; }
		constexpr size_t	dimention(satisfy::Integer auto rankPos) DUC_CONST_RNOEXCEPT {
			DUC_TEST_THROW((rankPos <= properties::rank) && (rankPos >= 0), "Rank outside tensor.\n");

			return properties::shape[rankPos];
		}

		// > Access functions and operators

		constexpr type& operator()(satisfy::Integer auto... indexes) DUC_RNOEXCEPT {

			constexpr uint16_t IndexCount = sizeof...(indexes);
			DUC_TEST_THROW(IndexCount > 0, "No indexes provided.");
			DUC_TEST_THROW(IndexCount <= rank(), "Amount of indexes provided exceed the tensor rank.");

			constexpr std::array<size_t, IndexCount> IndexesArray = { indexes... };

			DUC_TEST_THROW([&]() {
				for (size_t i = 0; i < IndexCount; ++i) {
					if (IndexesArray[i] >= shape(i)) {
						return false;
					}
				}
				return true;
			}(), "The indexes provided does not match the tensor shape.");

			constexpr std::array Multipliers = math_util::calculateMultipliers(shape());
			size_t index = 0;

			for (uint16_t i = 0; i <= rank(); i++) {
				DUC_TEST_THROW(IndexesArray[i] >= 0, "Negative indexes are not allowed.");
				DUC_TEST_THROW(IndexesArray[i] < shape(i), "The index is outside the tensor.\n(Max =" + duc::util::toChars(shape(i) - 1) + ", Attempted[" + duc::util ::toChars(IndexesArray[i]) + "])");

				index += IndexesArray[i] * Multipliers[i];
			}

			return _elements[index];

		}
		[[nodiscard]] constexpr const type& operator()(satisfy::Integer auto... indexes) DUC_RNOEXCEPT {
			return (*this)(indexes...);
		}

		constexpr type& operator [](size_t index) DUC_RNOEXCEPT {
			DUC_TEST_THROW(index < size(), "The index is outside the tensor. (Max = " + duc::util::toChars(size() - 1) + ")");

			return _elements[index];
		}
		[[nodiscard]] constexpr const type& operator [](size_t index) DUC_CONST_RNOEXCEPT {
			return (*this)[index];
		}

		constexpr type& operator [](satisfy::Integer auto... indexes) DUC_RNOEXCEPT {
			return (*this)(indexes...);
		}
		[[nodiscard]] constexpr const type& operator [](satisfy::Integer auto... indexes) DUC_CONST_RNOEXCEPT {
			return (*this)(indexes...);
		}

		// > Math operations functions and operators
		tensor& operator+(const tensor& other) DUC_RNOEXCEPT {
			DUC_TEST_ERROR(math_util::isTensorsShapeCompatible(rank(), shape(), other.shape()),
						   "The tensors must have a compatible shape.");

			for (size_t i = 0; i < this->size(); i++) {
				_elements[i] += other[i];
			}

			// Do Einstain Summation

			return this;
		}
		tensor& operator+(satisfy::Real auto scalar) {
			for (size_t i = 0; i < this->size(); i++) {
				_elements[i] += scalar;
			}
			return this;
		}

		tensor& operator-(const tensor& other) {
			DUC_TEST_ERROR(math_util::isTensorsShapeCompatible(rank(), shape(), other.shape()),
						   "The tensors must have a compatible shape."
			);

			for (size_t i = 0; i < this->size(); i++) {
				_elements[i] -= other[i];
			}

			// Do Einstain Summation

			return this;
		}
		tensor& operator-(satisfy::Real auto scalar) {
			for (size_t i = 0; i < this->size(); i++) {
				_elements[i] -= scalar;
			}
			return this;
		}

	private:

	};

	
}

#ifdef _STRING_
namespace std {

	std::string to_string(const duc::satisfy::Vector auto& vec) {
		std::string result = "<";
		result.reserve((vec.size() * 2) + 1);

		for (auto it = vec.cbegin(), end = vec.cend(); it != end; ++it) {
			result.append(std::to_string(*it));
			result.append(", ");
		}

		result.pop_back();
		result.pop_back();
		result.push_back('>');

		return result;
	}

	std::ostream& operator<<(std::ostream &stream, const duc::satisfy::Vector auto& vec) {
		return stream << std::to_string(vec);
	}

}


#endif