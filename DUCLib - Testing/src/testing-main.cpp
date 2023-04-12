#include <iostream>


#include <structures/vectorial.h>
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

template<auto...vals>
using vp = duc::math_utils::vectorial_properties<vals...>;

int main() {
    /// // srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	duc::vector<int, 3> v0 = { 1, 2, 3 };
	duc::vector<float, 3> v1 = { 2.3f, 5.32f, 4.7f };
	
	v0 += v1 * 10;
	std::cout << "<" << v0[0] << ", " << v0[1] << ", " << v0[2] << ">\n";
	v0 *= 3;
	std::cout << "<" << v0[0] << ", " << v0[1] << ", " << v0[2] << ">\n";
	v0 -= (v0 * 2) / (v1 * 5);
	std::cout << "<" << v0[0] << ", " << v0[1] << ", " << v0[2] << ">\n";
	-v0;
	std::cout << "<" << v0[0] << ", " << -v0[1] << ", " << (-v0)[2] << ">\n";

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

