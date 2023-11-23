#pragma once
#include <cudlib/macro_tools.h>

#include "../utilities/conventions.h"



namespace duc {
	template<class type = double>
	struct imaginary {
		type value = 0;


	};

	template<satisfy::Real type = double>
	class complex {
	public:
		using re_type = type;
		using im_type = imaginary<type>;

		re_type _real = 0;
		im_type _imaginary = 0;

	public:
		re_type real() { return _real; }
		im_type imag() { return _imaginary; }

		complex operator+(complex other);
		complex operator-(complex other);
		complex operator*(complex other);
		complex operator/(complex other);

		complex operator+(auto other);
		complex operator-(auto other);
		complex operator*(auto other);
		complex operator/(auto other);

		operator auto() DUC_CONST_RNOEXCEPT {
			return real();
		}
	};
}