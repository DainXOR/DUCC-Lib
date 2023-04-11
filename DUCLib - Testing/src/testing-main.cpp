#include <iostream>


#include <structures/vectorial.h>
#include <structures/polynomial.h>

#include <functions/arithmetic.h>
#include <utilities/dmutils.h>

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
    // srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	DUC_TEST(0 == 1, WARN, "Hmmm");

	DUC_TEST_FUNCTION(duc::fastInvSqrt(-5), INFINITY);
	//TEST_FUNCTION();
	auto[num, den] = duc::fraction<>::toFraction(5.4f);

	duc::fraction<>::toFraction(5.4f) == duc::fraction({ 27, 5 });

	std::cout << num << " / " << den << "\n";
	
	auto nums = generateRandomNumbers<float, float>(1000, { 0.f, 16.f }, { 0.f, 16.f });

	for (const auto& elem : nums) {
		std::apply([](const auto& n1, const auto& n2) {
			std::cout << "{" << n1 << ", " << n2 << "},";
		}, elem);
	}
	
	return 0;
}

