#include <iostream>

#include <duclib.h>


int main() {
	std::cout << duc::math_utils::require::Integral<char> << "\n";
	duc::vector<3, int> Hmmm;

	std::cout << duc::math_utils::require::Vector<duc::vector<2, int>> << "\n";

	// duc::math_utils::helper::tensor_properties_struct<1, 2, 3, 4, 5> Str;
	
	return 0;
}