#include <iostream>


#include <structures/vectorial.h>
#include <structures/polynomial.h>

#include <functions/arithmetic.h>
#include <utilities/dmutils.h>

// #include <complex>
// #include <string>
// #include <tuple>
#include <cmath>


#define DUCLIB_MACRO_TOOLS
#define DUCLIB_TESTING
#include <macro_tools.h>
#include <benchmark.h>								



template<auto...vals>
using vp = duc::math_utils::vectorial_properties<vals...>;

int main() {
    // srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    
	TEST_FUNCTION(duc::fastInvSqrt(-5), INFINITY);
	//TEST_FUNCTION();
	auto[num, den] = duc::fraction<>::toFraction(5.4f);

	duc::fraction<>::toFraction(5.4f) == duc::fraction({ 27, 5 });

	std::cout << num << " / " << den << "\n";
	
	return 0;
}

