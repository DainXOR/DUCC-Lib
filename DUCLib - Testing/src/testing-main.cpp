#include <iostream>
#include <vector>

#include <duclib.h>
#include "utilities/dmutils.h"

#define DUCLIB_MACRO_TOOLS
#define DUCLIB_TESTING
#include <macro_tools.h>

template<auto...vals>
using vp = duc::math_utils::vectorial_properties<vals...>;

int main() {

	constexpr uint8_t V = 5;

	duc::vector<V, float> tv{1, 2, 3, 4};

	std::cout << tv.fastMagnitude() << "\n";
	std::cout << tv.norm() << "\n";
	
	return 0;
}

