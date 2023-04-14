#include <iostream>


#include <structures/vectorial.h>
#include <structures/complex.h>
#include <structures/polynomial.h>

#include <functions/arithmetic.h>
#include <utilities/mutils.h>

// #include <complex>
// #include <string>
// #include <tuple>
#include <cmath>

#define DUCLIB_LOG
#include <macro_tools.h>
#include <benchmark.h>								


int main() {
    /// // srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	duc::complex<> c0 = { ._imaginary = 3 };

	duc::vector<3, float, float[3]> v0 = {{10, 20, 30}};
	duc::vector<3> v1 = { { 2.3f, 5.32f, 4.7f } };
	//duc::vector< 3, duc::complex<> > v3{ { {2, 4}, {5,7}, {3, 731} } };
	//v1 = v3;

	std::cout << noexcept(v0.size()) << "\n";
	std::cout << noexcept(v1.size()) << "\n";

	std::cout << std::is_aggregate_v<duc::vector<3, int>> << "\n";
	std::cout << std::is_aggregate_v<duc::vector<0, int>> << "\n";

	std::cout << duc::root(v0.fastMagnitude(), 2) << "\n";
	std::cout << v0.norm() << "\n";
	// v1 = v0;

	auto v2 = v0;
	v2.normalize();
	v0.fastNormalize();
	
	std::cout << "<" << v2[0] << ", " << v2[1] << ", " << v2[2] << ">\n";
	std::cout << "<" << v0[0] << ", " << v0[1] << ", " << v0[2] << ">\n";

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

