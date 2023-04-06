#include <iostream>


#include <structures/vectorial.h>
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
    
	TEST_FUNCTION(duc::abs(-4.324), 4.324);

	
	return 0;
}

