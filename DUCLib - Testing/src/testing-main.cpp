#include <iostream>


#include <structures/vector.h>
#include <functions/arithmetic.h>
#include <utilities/dmutils.h>

// #include <complex>
// #include <string>
#include <tuple>


#define DUCLIB_MACRO_TOOLS
#define DUCLIB_TESTING
#include <macro_tools.h>







template<auto...vals>
using vp = duc::math_utils::vectorial_properties<vals...>;

int main() {
    // srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    //
	duc::vector Test = { { 1, 4, 4.2f } };
	//Test = {};

	/*for (auto elem : Test) {
		std::cout << elem << "\n";
	}*/

	//std::cout << duc::exp(20, 0.5f) << "\n";
	//std::cout << duc::root(20, 2) << "\n";


    // for (int i = 0; i <= 100; ++i) {
    //     std::cout << "{" << i*i << ", " << i << "}, ";
    // }


	std::cout << std::boolalpha;

	std::cout << "Ceil: " << duc::ceil(8.5) << " -> 9 " << (duc::ceil(8.5) == 9) << "\n";
	std::cout << "Ceil: " << duc::ceil(-8.5) << " -> -8 " << (duc::ceil(-8.5) == -8) << "\n";
	std::cout << "Floor: " << duc::floor(8.5) << " -> 8 " << (duc::floor(8.5) == 8) << "\n";
	std::cout << "Floor: " << duc::floor(-8.5) << " -> -9 " << (duc::floor(-8.5) == -9) << "\n";
	std::cout << "Round: " << duc::round(8.5) << " -> 9 " << (duc::round(8.5) == 9) << "\n";
	std::cout << "Round: " << duc::round(-8.5) << " -> -8 " << (duc::round(-8.5) == -8) << "\n";

	return 0;
}

