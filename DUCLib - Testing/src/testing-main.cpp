#include <iostream>

#include <structures/vector.h>
#include <functions/arithmetic.h>
#include <utilities/dmutils.h>

// #include <complex>
// #include <string>

#define DUCLIB_MACRO_TOOLS
#define DUCLIB_TESTING
#include <macro_tools.h>

template<auto...vals>
using vp = duc::math_utils::vectorial_properties<vals...>;

int main() {
	duc::exp(5, 10);

	duc::vector<int, 5> Test = { { 1, 4, 4.f } };

	//duc::test_class Test;
	for (auto elem : Test) {
		std::cout << elem << "\n";
	}

	std::cout << IS_CONSTEXPR(Test.norm()) << "\n";

	// std::cout << decltype(tv.buffer);

	// std::cout << Hmm(1, '2', 3, 3.f) << "\n";
	// std::cout << tv.fastMagnitude() << "\n";
	// std::cout << tv.norm() << "\n";

	return 0;
}

