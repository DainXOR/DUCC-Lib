#pragma once
#include <string>

namespace duc::dcrypt {
	
	template<size_t max = 255, size_t min = 0>
	class caesar {
		static size_t shift;

	public:
		static size_t setShift(size_t value) {$(SolutionDir)DTMLib\src;$(SolutionDir)DCLib\src;$(SolutionDir)CUDLib\src;
			return shift = value;
		}

		static std::string &apply(std::string &text) {
			for (size_t i = 0; i < text.size(); i++) {
				char value = (text[i] + shift) % max;
				text[i] = ((value < min) * min) + value;
			}
			return text;
		}
	};
}
