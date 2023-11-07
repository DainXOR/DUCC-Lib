#include <iostream>

#include <structures/vectorial.h>
#include <structures/mtcomplex.h>
#include <structures/polynomial.h>

#include <functions/algorithm.h>
#include <functions/arithmetic.h>
#include <utilities/mutils.h>

//#include <experimental/sstring.h>
#include <dclib/structures/data_structures.h>
#include <dclib/utilities/conventions.h>
#include <dclib/experimental/dijkstra.h>


// #include <complex>
// #include <string>
#include <tuple>
#include <cmath>
#include <numeric>

#define DUCLIB_LOG
#include <macro_tools.h>							

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
	class caesar {
		static size_t shift;

	public:
		static size_t setShift(size_t value) {
			return shift = value;
		}

		static std::string apply(std::string text, size_t shiftValue = shift) {
			shift = shiftValue;

			for (size_t i = 0; i < text.size(); i++) {
				uint8_t value = ((text[i] + shift) % (max - min)) + min;
				text[i] = value;
			}
			return text;
		}
		static std::string reverse(std::string text, size_t shiftValue = shift) {
			shift = shiftValue;

			for (size_t i = 0; i < text.size(); i++) {
				uint8_t value = (text[i] - shift) % (max - min);
				value += value < 0 ? max : min;
				text[i] = value;
			}
			return text;
		}
	};

	template<size_t max, size_t min>
	size_t caesar<max, min>::shift = 0;

	template<size_t p1, size_t p2, size_t p3, size_t g>
	class diffie_hellmann {
		size_t ka;
		size_t kb;

	public:
		diffie_hellmann() {
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

template<uint8_t option>
void cipherTest() {
	if constexpr (option == 1) {
		std::string str = "me gusta el mango", enc;

		hola::caesar<> c1; // Fix non ascii and min offset

		c1.setShift(100);

		std::cout << str << "\n";
		std::cout << (enc = c1.apply(str)) << "\n";
		std::cout << c1.reverse(enc) << "\n";
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

void graphTest() {
	/*
	duc::ex::graph<uint16_t> g1;
	g1.getNode(0)->getConnections();

	g1.emplaceNode(10);
	g1.emplaceNode(11);
	g1.emplaceNode(12);
	g1.emplaceNode(13);

	//t_info<duc::ex::graph<int>>;
	v_info<0>;

	constexpr bool r = duc::satisfy::WeightedNode<duc::ex::wnode<int>>;

	//for (auto &node : g1.getNodes()) {
	//	std::cout << "Node " << node.getID() << ": ";
	//	std::cout << node.getElement();
	//	std::cout << "\n";
	//}
	
	g1.createConnection(1, 2, 54);
	g1.createConnection(1, 3, 21);
	g1.createConnection(1, 4, 122);

	g1.createConnection<false>(2, 4, 62);
	g1.createConnection(2, 3, 12);

	g1.createConnection(3, 4, 5);

	//duc::ex::alg::dijkstra<duc::ex::graph<int>> d = {};

	d.setGraph(g1);
	auto test = d.search(1, 4);


	//for (auto id : g1.getNodesIDs()) {
	//	std::puts(std::format("Node {0}: ", id).c_str());
	//	for (auto &[id, route] : g1.getRoutesOf(id)) {
	//		std::puts(std::format("- To {0}: <{1}>", id, route).c_str());
	//	}
	//}
	*/
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

int main() {

	//std::cout << std::to_string(duc::alg::prime_sequence<100>::get()) << "\n";
	
	duc::util::expansion t1 = duc::util::expand<5, 1>;
	duc::util::expansion t2 = duc::util::replicate<4, '1', '2'>;
	duc::util::expansion t3 = duc::util::clone<4, '1', '2'>;
	duc::util::expansion t4 = duc::util::echo<3, 1, 2, 3>;

	duc::util::expansion t5 = duc::util::sequence<15, 3, 3>;
	duc::util::expansion t6 = duc::util::primeSequence<50, 11, 11>;
	duc::util::expansion t7 = duc::util::sequence<111, 11, 1, hyper_eleven>;

	constexpr bool hmmm_ = hyper_eleven<bool, 11111111>{}();
	constexpr auto digs = duc::digits(11111111);

	std::cout << typeid(t7).name() << "\n";

	constexpr bool tdf = duc::satisfy::ConstexprCallable<duc::util::is_prime, bool, int64_t>;

	graphTest();
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

	t.insert(2, 0u);
	t.insert(3, 1u);
	t.insert(4, 0u, 0u);
	t.insert(5, 1u, 0u);
	t.insert(6, 1u, 1u);
	t.insert(7, std::array{ 1ull, 0ull, 0ull });

	//std::vector v = t.getAsArray(Traverse::IN_ORDER);
	//for (auto node : v) {
	//	std::cout << node->element << " -> ";
	//}

	std::cout << std::convertible_to<duc::traits::Queue, int>;
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