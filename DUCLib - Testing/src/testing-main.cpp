#include <iostream>

#include <structures/vectorial.h>
#include <structures/mtcomplex.h>
#include <structures/polynomial.h>

#include <functions/arithmetic.h>
#include <utilities/mutils.h>

//#include <experimental/sstring.h>
#include <structures/data_structures.h>

// #include <complex>
// #include <string>
#include <tuple>
#include <cmath>

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
}




int main() {
	std::cout << hola::division(27, 3) << "\n";


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