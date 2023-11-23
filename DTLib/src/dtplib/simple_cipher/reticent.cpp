#include "reticent.hpp"



namespace duc {

	bool reticent::configure(cypher c, key_type k) noexcept {
		reticent::_cypher = c;
		reticent::_key_type = k;
		return true;
	}
}

