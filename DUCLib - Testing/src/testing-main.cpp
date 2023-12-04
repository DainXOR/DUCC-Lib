#include <iostream>

#define DUCLIB_LOG
#include <cudlib/macro_tools.h>

#include <dtmlib/structures/vectorial.h>
#include <dtmlib/structures/mtcomplex.h>
#include <dtmlib/structures/polynomial.h>

#include <dtmlib/functions/algorithm.h>
#include <dtmlib/functions/arithmetic.h>

#include <dtmlib/utilities/mutils.h>

//#include <dclib/experimental/sstring.h>

#include <C:/dev/cpp/libs/DUCLib - Proyect/DCLib/src/dclib/structures/data_structures.h>
#include <dclib/utilities/conventions.h>
#include <dclib/experimental/dijkstra.h>

// #include <complex>
// #include <string>
#include <tuple>
#include <cmath>
#include <numeric>
#include <queue>
#include <stack>
#include <map>



template<class structure, class string_type>
void propertiesTests(string_type);
void temp();


namespace hola {
	int division(int dividendo, int divisor) {
		int a = 0;
		return ((!(dividendo < divisor) && (a = 1 + division(dividendo - divisor, divisor))), a);
	}

	//template<typename ..._types>
	//int print(const std::format_string<_types...> fmt, _types&&... args) {
	//	return std::puts(std::format(fmt, args...).c_str());
	//}

	template<size_t size>
	void test(std::array<char, size> str) {}

	template<size_t size>
	using string = std::array<char, size>;

	//template<size_t size>
	using rstring = char[];

	template<size_t max = 255, size_t min = 0>
	//requires (max > min)
	class caesar {
		static size_t shift;

	public:
		static size_t setShift(size_t value) {
			return shift = value;
		}

		static std::string apply(std::string text, size_t key = shift) {
			shift = key;
			uint8_t c = 0;

			for (size_t i = 0; i < text.size(); i++) {
				uint8_t value = ((uint8_t(text[i]) + shift) % (max - min)) + min;
				c = value;
			}
			return text;
		}
		static std::string reverse(std::string text, size_t key) {
			key = -key;

			for (size_t i = 0; i < text.size(); i++) {
				uint8_t value = (uint8_t(text[i]) - key);
				value += value < 0 ? -1 - value : value;
				text[i] = value;
			}
			return text;
		}
	};

	template<size_t max, size_t min>
	size_t caesar<max, min>::shift = 0;

	template<size_t p1, size_t p2, size_t p3 /* Big */, size_t g /* Small */>
	class diffie_hellmann {
		size_t ka;
		size_t kb;

	public:
		diffie_hellmann() {
			// Server			||		  Client1       ||       Client2       ||       Client3 ...
			// g, p3			->
			//					<-		 g^a % p3			    g^b % p3 	           g^c % p3 ...
			// ga, gb, gc, ...	->	   gb^a, gc^a...	      ga^gc^... % p3	    ga^gb^... % p3 ...
			//                          gabc... % p3		   gabc... % p3	         gabc... % p3 ...

			constexpr size_t gna = duc::pow(g, p1);
			constexpr size_t gnb = duc::pow(g, p2);


			constexpr size_t atb = gna % p3;
			constexpr size_t bta = gnb % p3;

			ka = size_t(duc::pow(bta, p1)) % p3;
			kb = size_t(duc::pow(atb, p2)) % p3;
		}

		duc::pair<size_t> getValues() {
			return { ka, kb };
		}
	};
}
namespace std {
	template<std::ranges::range type>
	string to_string(type arr) {
		string result;
		result.reserve(arr.size() * 3);

		for (auto value : arr) {
			result += to_string(value) + ", ";
		}
		result.pop_back();
		result.pop_back();

		return result;
	}
	template<class t>
	string to_string(duc::ex::xnode<t> node) {
		string result;

		result += "[";
		result += to_string(node.getID());
		result += ": "; 
		result += to_string(node.getElement()); 
		result += "]";

		return result;
	}

	template<class T, class CharT>
	struct std::formatter<std::vector<T>, CharT> : std::formatter<const char*, CharT> {

		template<class FormatContext>
		auto format(std::vector<T> v, FormatContext& fc) const {
			return std::formatter<const char*, CharT>::format(std::to_string(v).c_str(), fc);
		}
	};
	template<class T, size_t s, class CharT>
	struct std::formatter<std::array<T, s>, CharT> : std::formatter<const char*, CharT> {

		template<class FormatContext>
		auto format(std::array<T, s> a, FormatContext& fc) const {
			return std::formatter<const char*, CharT>::format(std::to_string(a).c_str(), fc);
		}
	};
	template<class T, class CharT>
	struct std::formatter<duc::ex::xnode<T>, CharT> : std::formatter<const char*, CharT> {

		template<class FormatContext>
		auto format(duc::ex::xnode<T> n, FormatContext& fc) const {
			return std::formatter<const char*, CharT>::format(std::to_string(n).c_str(), fc);
		}
	};
}
namespace duc {

	class numberx {
		friend class builder;

		std::vector<uint8_t> buffer;
		uint8_t sign;
		size_t digits;

	public:
		numberx() : buffer(), sign(1), digits(0) {}
		class builder {
			std::stack<uint8_t> buffer;
			uint8_t sign;

		public:
			builder() : buffer(), sign(1) {}

			builder& setNegative(uint8_t sign) {
				this->sign = -1;
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
}

template<uint8_t option>
void cipherTest() {
	if constexpr (option == 1) {
		std::string str = "me gusta el mango", enc;

		hola::caesar<> c1; // Fix non ascii and min offset

		c1.setShift(100);

		std::cout << str << "\n";
		std::cout << (enc = c1.apply(str)) << "\n";
		//std::cout << c1.reverse(enc) << "\n";
	}
	else if constexpr (option == 2) {
		hola::diffie_hellmann<29, 19, 53, 2> dh;

		auto [a, b] = dh.getValues();
		std::cout << a << ", " << b << "\n";
	}
}

template<class t>
using t_info = duc::util::type_info<t>;
template<auto v>
using v_info = duc::util::var_info<v>;

template<class type, duc::traits::Graph traits>
void printGraphData(duc::ex::graph<type, traits> graph) {
	for (auto id1 : graph.getNodesIDs()) {
		std::puts(std::format("Node {0}: ", id1).c_str());
		for (auto &[id2, route] : graph.getRoutesOf(id1)) {
			std::puts(std::format("- To {0}: <{1}>", id2, route.first).c_str());
		}
	}
	return;
}

template <class compare_t, template <class> class comp = std::less>
struct compare_first {
	[[nodiscard]]
	constexpr bool operator()(const auto& left, const auto& right) const noexcept {
		return comp<compare_t>{}(left.first, right.first);
	}
};
template <class compare_t, template <class> class comp = std::less>
struct compare_second {
	[[nodiscard]]
	constexpr bool operator()(const auto& left, const auto& right) const noexcept {
		return comp<compare_t>{}(left.second, right.second);
	}
};

void graphTest() {
	constexpr duc::traits::Graph gt = duc::traits::Graph::DIRECTED | duc::traits::Graph::WEIGHTED;
	duc::ex::graph<uint32_t, gt> g1 = {};

	g1.emplace(10);
	g1.emplace(11);
	g1.emplace(12);
	g1.emplace(13);
	g1.emplace(14);
	g1.emplace(15);
	
	g1.createConnection(1, 2, 16);
	g1.createConnection(1, 3, 12);
	g1.createConnection(1, 5, 21);

	g1.createConnection(2, 5, 6);
	g1.createConnection(2, 6, 1);

	g1.createConnection(3, 2, 1);
	g1.createConnection(3, 4, 5);

	g1.createConnection(4, 5, 3);

	g1.createConnection(6, 4, 2);

	printGraphData(g1);

	duc::ex::alg::dijkstra algorithm = { g1 };
	auto finalRoute = algorithm.search(1, 5);

	std::cout << "\n";
	std::cout << finalRoute.second << ": ";
	std::cout << std::to_string(finalRoute.first) << "\n";
	//auto test = d.search(1, 4);
}

template<class, int64_t number>
struct hyper_eleven {
	constexpr bool operator()() {
		return check(number, duc::util::expand<duc::digits(number), 10ll>);
	}

	template<int64_t... I>
	constexpr bool check(int64_t num, duc::util::expansion<I...>) {
		(((num % I) == 1 && (num /= I)) &&...);
		return num == 0;
	}
};

void templateBending() {
	duc::util::expansion t1 = duc::util::expand<5, 1>;
	duc::util::expansion t2 = duc::util::replicate<4, '1', '2'>;
	duc::util::expansion t3 = duc::util::clone<4, '1', '2'>;
	duc::util::expansion t4 = duc::util::echo<3, 1, 2, 3>;

	duc::util::expansion t5 = duc::util::sequence<15, 3, 3>;

	duc::util::expansion t6 = duc::util::primeSequence<50>;
	std::cout << typeid(t6).name() << "\n";


	duc::util::expansion t7 = duc::util::sequence<111, 11, 1, hyper_eleven>;

	std::array t8 = duc::util::asArray(duc::util::sequence<15, 3, 3>);

	for (auto value : t8) {
		std::cout << value << " ";
	}
	std::cout << "\n";

	constexpr bool hmmm_ = hyper_eleven<bool, 11111111>{}();
	constexpr auto digs = duc::digits(11111111);

	//std::cout << typeid(t7).name() << "\n";

	constexpr bool tdf = duc::satisfy::ConstexprCallable<hyper_eleven, bool, int64_t>;
	//std::cout << std::to_string(duc::alg::prime_sequence<100>::get()) << "\n";
}

void printNodeAndSiblings(auto* parent) {
	std::cout << parent->getID() << ">-(" << parent->getElement() << ") -> ";

	for (size_t i = 0; i < parent->getSiblingCount(); i++) {
		std::cout << "[" << parent->getSibling(i)->getID() << ": "
					<< parent->getSibling(i)->getElement() << "] | ";
	}
	std::cout << "\n";
	return;
}


void numberxTest() {
	duc::numberx n1 = duc::numberx::builder()
		.addDigits(35400, 12345678, 987654321)
		.build();

	duc::numberx n2 = duc::numberx::builder()
		.addDigit(5)
		.addDigit(9)
		.addDigit(0)
		.addDigit(1)
		.build();

	std::cout << (n1 <= n2) << "\n";

	std::cout << n1 << "\n";
	std::cout << n2 << "\n";


	auto nxComp = n1 <=> n2;
	auto pComp = n1 <=> 420;


	auto nxSum = n1 + n2;
	auto pSum = n1 + 420;

	auto nxSub = n1 - n2;
	auto pSub = n1 - 420;

	auto nxMul = n1 * n2;
	auto pMul = n1 * 420;

	auto nxDiv = n1 / n2;
	auto pDiv = n1 / 420;

	auto nxMod = n1 % n2;
	auto pMod = n1 % 420;


	auto nxAnd = n1 & n2;
	auto pAnd = n1 & 420;

	auto nxOr = n1 | n2;
	auto pOr = n1 | 420;

	auto nxXor = n1 ^ n2;
	auto pXor = n1 ^ 420;
}


int main() {
	srand(time(NULL));



	//graphTest();
	//mainDijkstra();
	//cipherTest<2>();

	//std::cout << (24 + 100) % 27;

	//hola::print("{0}", hola::division(27, 3));
	//std::puts(std::format("{0}", "f").c_str());
	//hola::test("");

	//std::puts(std::format("hmmm1: {0}", 1).c_str());
	//std::puts(std::format("hmmm2: {0}", 2).c_str());

	//constexpr hola::sequence c;
	//constexpr auto values = c.get();
	//constexpr bool is = noexcept(values);
	//if constexpr (is) {
	//	for (size_t i = 0; i < c.size(); i++) {
	//		std::cout << values[i] << " ";
	//	}
	//}

	

	/*
	using namespace duc::ex;
	bi_tree<int> t(bi_tree<int>::createNode(1));
	
	volatile auto a = std::tuple{ 0, ",wdq", 34.2f};

	t.insert(2, 1u);
	t.insert(3, 1u);
	t.insert(10, 0u);

	t.insert(4, 1u, 1u);
	t.insert(5, 1u, 0u);
	t.insert(6, 1u, 1u);
	t.insert(8, 1u, 1u, 1u);
	t.insert(6, 1u, 1u);
	t.insert(6, 0u, 0u);
	t.insert(6, 0u, 0u, 0u);
	t.insert(7, std::array{ 1ull, 1ull, 1ull });
	t.insert(7, std::array{ 1ull, 1ull, 1ull, 1ull });

	std::vector v = t.getAsArray(duc::traits::Traverse::IN_ORDER);
	for (auto node : v) {
		std::cout << node->element << " -> ";
	}
	std::cout << "\n\n";

	std::cout << t.depth();
	std::cout << "\n";
	*/

	return 0;

}

template<class structure, class string_type>
void propertiesTests(string_type strName) {

	std::cout << strName << ":\n";
	//std::cout << "- Satisfies Vector: " << duc::satisfy::Vector<structure> << "\n";
	std::cout << "- Is aggregate: " << std::is_aggregate_v<structure> << "\n";
	//std::cout << "- Aggregate set r: " << std::is_aggregate_v<duc::vector<3, int>> << "\n";
	
}

void temp() {
	/// // srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	DUC_SATISFIES(_HAS_CXX23, "Required c++23 to run the library.");

	//propertiesTests();
	// duc::complex<> c0 = { ._imaginary = 3 };

	duc::vector<3> v0 = { {10, 20, 30} };
	const duc::vector<3> v1 = { { 2.3f, 5.32f, 4.7f } };

	duc::matrix m0;

	duc::vector v2 = v0 + v1;


	//std::cout << v2[0] << v2[1] << v2[2] << "\n";
	//std::cout << v1.at(0) << v1.at(1) << v1.at(2) << "\n";

	std::cout << v0.dotProduct(std::array{ 1, 2, 3 });

	//duc::vector<3, duc::complex<>> v3{ { {2, 4}, {5,7}, {3, 731} } };
	//v1 = v3;


	//T1.angle(T2);
	//DUC_INFO_LOG(v0.angle(v1));


	/*
	auto[num0, den0] = duc::toFraction(0.4);
	auto[num1, den1] = duc::toFraction(5.4f);
	auto[num2, den2] = duc::toFraction(0.285f);
	auto[num3, den3] = duc::toFraction(1.727f);

	std::cout << num0 << " / " << den0 << "\n";
	std::cout << num1 << " / " << den1 << "\n";
	std::cout << num2 << " / " << den2 << "\n";
	std::cout << num3 << " / " << den3 << "\n";
	*/

	// auto nums = generateRandomNumbers<float, float>(1000, { 0.f, 16.f }, { 0.f, 16.f });
	// 
	// for (const auto& elem : nums) {
	// 	std::apply([](const auto& n1, const auto& n2) {
	// 		std::cout << "{" << n1 << ", " << n2 << "},";
	// 	}, elem);
	// }
}