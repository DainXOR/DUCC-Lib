#pragma once

#include <cudlib/template_bending/experimental.hpp>

#include "../utilities/conventions.h"


namespace duc::ex {
	/// > Declarations

	template<satisfy::Integer digit_size = uint8_t, class container = std::vector<digit_size>>
	class basex;

	template<size_t maxBytes = 0, uint64_t bytesPerSection = 1, class byte_t = traits::fit_8bits<bytesPerSection>,
		class container_t = conditional::array_or_vector_256bmax<byte_t, byte_t>>
		class numberx;

	template<satisfy::UnsignedInteger number_t, size_t max2Pow = 64, size_t precision = 5>
	class multy_number;

	/// > Definitions

	template<satisfy::Integer digit_size, class container>
	class basex {
	public:
		container _buffer;
	public:
		basex() {}
	};


	template<size_t maxBytes, uint64_t bytesPerSection, class byte_t, class container_t>
	class numberx {
		friend class builder;

		container_t buffer;
		uint8_t sign;
		size_t digits;

	public:
		numberx() : buffer(), sign(1), digits(0) {}

		class builder {
			std::stack<uint8_t> buffer;
			uint8_t sign;

		public:
			builder() : buffer(), sign(1) {}

			builder& setNegative(bool isNegative) {
				this->sign = isNegative * -1;
				return *this;
			}
			builder& addDigit(int8_t digit) {
				this->buffer.push(digit > 9 ? 9 : digit);
				return *this;
			}

			template<class ...uints>
			builder& addDigits(uint64_t num, uints ...tail) {
				this->addNumber(num);

				if constexpr (sizeof...(tail) != 0) {
					this->addDigits(tail...);
				}
				return *this;
			}

			numberx build() {
				numberx n;
				n.sign = this->sign;
				n.digits = this->buffer.size();


				while (this->buffer.size() > 1) {
					uint8_t leftDigit = this->buffer.top();
					this->buffer.pop();
					uint8_t rightDigit = this->buffer.top();
					this->buffer.pop();

					leftDigit <<= 4;
					leftDigit |= rightDigit;
					n.buffer.push_back(leftDigit);
				}

				if (this->buffer.size() == 1) {
					n.buffer.push_back(this->buffer.top() << 4);
					this->buffer.pop();
				}

				return n;
			}

		private:

			builder& addNumber(int64_t num) {
				uint16_t digits = duc::digits(num);
				uint64_t pow10 = duc::pow(10, digits - 1);

				while (digits > 0) {
					uint64_t digit = num / pow10;
					this->addDigit(digit);
					num -= digit * pow10;
					pow10 /= 10;
					digits--;
				}
				return *this;
			}
		};

		int8_t getDigit(int64_t index) const {
			if (index > this->digits) {
				return -1;
			}

			int8_t digit = this->buffer[index >> 1];
			index & 0b1 ?
				digit &= 0b00001111 :
				digit >>= 4;

			return digit;
		}

		std::strong_ordering operator<=>(const numberx& n) const noexcept {
			if (this->digits != n.digits) {
				return this->digits <=> n.digits;
			}

			for (int64_t i = this->digits; i > 0; i--) {
				if (this->buffer[i - 1] != n.buffer[i - 1]) {
					return this->buffer[i - 1] <=> n.buffer[i - 1];
				}
			}
			return std::strong_ordering::equal;
		}
		std::strong_ordering operator<=>(const int64_t& n) const noexcept {
			return *this <=> numberx::builder().addDigits(n).build();
		}

		bool operator==(const numberx& n) const noexcept = default;
		bool operator==(const int64_t& n) const noexcept {
			return *this == numberx::builder().addDigits(n).build();
		}

		numberx operator+(const numberx& other) {
			numberx result;
			result.sign = this->sign;

			result.sign = *this > other ? this->sign : other.sign;
			result.digits = std::min(this->digits, other.digits);

			int8_t carry = 0;

			int8_t carrySign = 0;

			for (int64_t i = 0; i < (result.digits >> 1); i++) {
				// Value, carry, sign
				auto sumBack = this->adder(this->getDigit(i) * this->sign, other.getDigit(i) * other.sign);
				auto sumFront = this->adder(this->getDigit(i + 1) * this->sign, other.getDigit(i + 1) * other.sign);

				auto sumBackWithCarry = this->adder(sumBack.first * sumBack.third, carry * carrySign);
				auto sumFrontWithCarry = this->adder(sumFront.first * sumFront.third, sumBackWithCarry.first * sumBackWithCarry.third);

				result.buffer.push_back(sumBack.first | (sumFront.first << 4));

				carry = sumFrontWithCarry.second;
				carrySign = sumFrontWithCarry.third;
			}
			if (carry) {
				result.buffer.push_back(carry);
				result.digits++;
			}

			return result;
		}
		numberx operator+(int64_t number) {
			return *this + numberx::builder().addDigits(number).build();
		}

		numberx operator*(const numberx& other) {
			numberx result;
			result.sign = this->sign * other.sign;
			result.digits = this->digits + other.digits;

			int8_t carry = 0;
			int8_t carrySign = 0;

			for (int64_t i = 0; i < (result.digits >> 1); i++) {
				int8_t sum = 0;
				for (int64_t j = 0; j <= i; j++) {
					sum += this->getDigit(j) * this->sign * other.getDigit(i - j) * other.sign;
				}
				auto sumWithCarry = this->adder(sum, carry * carrySign);

				result.buffer.push_back(sumWithCarry.first);
				carry = sumWithCarry.second;
				carrySign = sumWithCarry.third;
			}
			if (carry) {
				result.buffer.push_back(carry);
				result.digits++;
			}

			return result;
		}
		numberx operator*(int64_t number) {
			return *this * numberx::builder().addDigits(number).build();
		}

		numberx operator-(const numberx& other) {
			numberx copy = other;
			copy.sign *= -1;
			return *this + copy;
		}
		numberx operator-(int64_t number) {
			return *this - numberx::builder().addDigits(number).build();
		}

		numberx operator/(const numberx& other) {
			numberx result;
			result.sign = this->sign * other.sign;
			result.digits = this->digits - other.digits;

			int8_t carry = 0;
			int8_t carrySign = 0;

			for (int64_t i = 0; i < (result.digits >> 1); i++) {
				int8_t sum = 0;
				for (int64_t j = 0; j <= i; j++) {
					sum += this->getDigit(j) * this->sign * other.getDigit(i - j) * other.sign;
				}
				auto sumWithCarry = this->adder(sum, carry * carrySign);

				result.buffer.push_back(sumWithCarry.first);
				carry = sumWithCarry.second;
				carrySign = sumWithCarry.third;
			}
			if (carry) {
				result.buffer.push_back(carry);
				result.digits++;
			}

			return result;
		}
		numberx operator/(int64_t number) {
			return *this / numberx::builder().addDigits(number).build();
		}

		numberx operator%(const numberx& other) {
			numberx result;
			result.sign = this->sign * other.sign;
			result.digits = this->digits - other.digits;

			int8_t carry = 0;
			int8_t carrySign = 0;

			for (int64_t i = 0; i < (result.digits >> 1); i++) {
				int8_t sum = 0;
				for (int64_t j = 0; j <= i; j++) {
					sum += this->getDigit(j) * this->sign * other.getDigit(i - j) * other.sign;
				}
				auto sumWithCarry = this->adder(sum, carry * carrySign);

				result.buffer.push_back(sumWithCarry.first);
				carry = sumWithCarry.second;
				carrySign = sumWithCarry.third;
			}
			if (carry) {
				result.buffer.push_back(carry);
				result.digits++;
			}

			return result;
		}
		numberx operator%(int64_t number) {
			return *this % numberx::builder().addDigits(number).build();
		}

		numberx operator&(const numberx& other) {
			numberx result;
			result.sign = this->sign * other.sign;
			result.digits = this->digits - other.digits;

			int8_t carry = 0;
			int8_t carrySign = 0;

			for (int64_t i = 0; i < (result.digits >> 1); i++) {
				int8_t sum = 0;
				for (int64_t j = 0; j <= i; j++) {
					sum += this->getDigit(j) * this->sign * other.getDigit(i - j) * other.sign;
				}
				auto sumWithCarry = this->adder(sum, carry * carrySign);

				result.buffer.push_back(sumWithCarry.first);
				carry = sumWithCarry.second;
				carrySign = sumWithCarry.third;
			}
			if (carry) {
				result.buffer.push_back(carry);
				result.digits++;
			}

			return result;
		}
		numberx operator&(int64_t number) {
			return *this & numberx::builder().addDigits(number).build();
		}

		numberx operator|(const numberx& other) {
			numberx result;
			result.sign = this->sign * other.sign;
			result.digits = this->digits - other.digits;

			int8_t carry = 0;
			int8_t carrySign = 0;

			for (int64_t i = 0; i < (result.digits >> 1); i++) {
				int8_t sum = 0;
				for (int64_t j = 0; j <= i; j++) {
					sum += this->getDigit(j) * this->sign * other.getDigit(i - j) * other.sign;
				}
				auto sumWithCarry = this->adder(sum, carry * carrySign);

				result.buffer.push_back(sumWithCarry.first);
				carry = sumWithCarry.second;
				carrySign = sumWithCarry.third;
			}
			if (carry) {
				result.buffer.push_back(carry);
				result.digits++;
			}

			return result;
		}
		numberx operator|(int64_t number) {
			return *this | numberx::builder().addDigits(number).build();
		}

		numberx operator^(const numberx& other) {
			numberx result;
			result.sign = this->sign * other.sign;
			result.digits = this->digits - other.digits;

			int8_t carry = 0;
			int8_t carrySign = 0;

			for (int64_t i = 0; i < (result.digits >> 1); i++) {
				int8_t sum = 0;
				for (int64_t j = 0; j <= i; j++) {
					sum += this->getDigit(j) * this->sign * other.getDigit(i - j) * other.sign;
				}
				auto sumWithCarry = this->adder(sum, carry * carrySign);

				result.buffer.push_back(sumWithCarry.first);
				carry = sumWithCarry.second;
				carrySign = sumWithCarry.third;
			}
			if (carry) {
				result.buffer.push_back(carry);
				result.digits++;
			}

			return result;
		}
		numberx operator^(int64_t number) {
			return *this ^ numberx::builder().addDigits(number).build();
		}

		friend std::ostream& operator<<(std::ostream& os, const numberx& n) {
			std::string rep;
			for (int64_t i = n.buffer.size(); i > 0; i--) {

				auto left = n.buffer[i - 1] >> 4;
				auto right = n.buffer[i - 1] & 0x0f;

				if (i < n.buffer.size() || !(n.digits & 0b1)) {
					rep += std::to_string(right);
				}
				rep += std::to_string(left);
			}
			os << rep;
			return os;
		}

	private:
		duc::triplet<int8_t> adder(int16_t left, int16_t right) {
			int16_t result = left + right;
			int8_t sign = result > 0 ? 1 : -1;
			result *= sign;
			int8_t carry = result >> 8;

			return { int8_t(result & 0b11111111), carry, sign };
		}

		duc::triplet<int8_t> multiplier(int16_t left, int16_t right) {
			int16_t result = left * right;
			int8_t sign = result > 0 ? 1 : -1;
			result *= sign;
			int8_t carry = result >> 8;

			return { int8_t(result & 0b11111111), carry, sign };
		}
	};

	template<satisfy::UnsignedInteger number_t, size_t max2Pow, size_t precision>
	class multy_number {
	public:
		size_t buffer = 1;
		size_t storedCount = 0;
		type::numberx<max2Pow / 8> buffer;

		constexpr static size_t maxPrime = 11 * (float(max2Pow) / 64);
		constexpr static size_t primeCount = duc::alg::primesTo<maxPrime>.size();


	public:
		bool contains(number_t number) {
			for (auto p : duc::alg::primesTo<maxPrime>) {
				size_t count = 0;
				size_t aux = this->buffer;

				while (duc::mod(aux, p) <= duc::mutil::error<precision>) {
					aux /= p;
					count++;
				}

				if (count == number) {
					return true;
				}
			}
			return false;
		}

		bool add(number_t number) {
			if (primeCount <= this->storedCount || this->contains(number))
				return false;

			size_t prime = duc::alg::primesTo<maxPrime>[this->storedCount];
			this->buffer *= duc::pow(prime, number);
			this->storedCount++;
			return true;
		}
		bool remove(number_t number) {
			for (auto p : duc::alg::primesTo<maxPrime>) {
				size_t count = 0;
				size_t aux = this->buffer;

				while (duc::mod(aux, p) <= duc::mutil::error<precision>) {
					aux /= p;
					count++;
				}

				if (count == number) {
					this->buffer = aux;
					return true;
				}
			}
			return false;
		}

		number_t retrieve(size_t pos) {
			size_t p = duc::alg::primesTo<maxPrime>[pos];
			size_t count = 0;
			size_t aux = this->buffer;

			while (duc::mod(aux, p) <= duc::mutil::error<precision>) {
				aux /= p;
				count++;
			}

			return count;
		}
		auto retrieveAll() {
			std::array<number_t, primeCount> values = {};

			for (size_t i = 0; i < primeCount; i++) {
				size_t p = duc::alg::primesTo<maxPrime>[i];
				size_t count = 0;
				size_t aux = this->buffer;

				while (duc::mod(aux, p) <= duc::mutil::error<precision>) {
					aux /= p;
					count++;
				}

				values[i] = count;
			}
			return values;
		}

		bool reencode() {
			auto values = this->retrieveAll(); // Sort values (n > 0)


			return false;
		}
	};
}