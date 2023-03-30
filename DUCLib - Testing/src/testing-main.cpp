#include <iostream>

#include <duclib.h>

template<auto...vals>
using vp = duc::math_utils::template_traits::vectorial_properties<vals...>;

int main() {

	constexpr unsigned short V = 5;

	duc::vector<V, char> tv;

	std::cout << (typeid(decltype(tv)::properties)).name();

	std::cout << vp<V>::size;
	std::cout << vp<5>::rank;

	for (auto e : vp<5>::dimentions ) {
		std::cout << e;
	}

	std::array arr = vp<5>::dimentions;
	
	return 0;
}