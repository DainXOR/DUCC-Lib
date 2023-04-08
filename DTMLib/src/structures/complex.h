#pragma once

#include "../utilities/constrains.h"

namespace duc {
	template<require::Real type = double>
	struct imaginary {
		type value = 0;



	};

	template<require::Real type = double>
	class complex {
	public:
		using re_type = type;
		using im_type = imaginary<type>;

	public:
		re_type real = 0;
		im_type imaginary = 0;
	};
}