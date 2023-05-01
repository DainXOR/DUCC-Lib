#include <iostream>


#include <structures/vectorial.h>
#include <structures/mtcomplex.h>
#include <structures/polynomial.h>

#include <functions/arithmetic.h>
#include <utilities/mutils.h>

// #include <complex>
// #include <string>
// #include <tuple>
#include <cmath>

#define DUCLIB_LOG
#include <macro_tools.h>							

void propertiesTests();

int main() {
    /// // srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	DUC_SATISFIES(_HAS_CXX23, "Required c++23 to run the library.");

	propertiesTests();
	// duc::complex<> c0 = { ._imaginary = 3 };

	duc::vector<3> v0 = { {10, 20, 30} };
	const duc::vector<3> v1 = { { 2.3f, 5.32f, 4.7f } };

	duc::matrix m0;

	duc::vector v2 = v0 + v1;

	//std::cout << v2[0] << v2[1] << v2[2] << "\n";
	//std::cout << v1.at(0) << v1.at(1) << v1.at(2) << "\n";

	std::cout << std::to_string(v0);

	std::array<int, 3> Hm = {};
	auto t = std::begin(Hm);
	auto v = *t;

	for (auto a : Hm) {}

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
	
	return 0;
}


void propertiesTests() {

	std::cout << "Vector:\n";
	std::cout << "- Satisfies Vector: " << duc::satisfy::Vector<duc::vector<>> << "\n";
	std::cout << "- Aggregate default: " << std::is_aggregate_v<duc::vector<>> << "\n";
	std::cout << "- Aggregate set r: " << std::is_aggregate_v<duc::vector<3, int>> << "\n";
	
}