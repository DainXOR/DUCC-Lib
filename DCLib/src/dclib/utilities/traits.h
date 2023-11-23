#pragma once

namespace duc::traits {
	enum Traverse {
		PRE_ORDER,
		POST_ORDER,
		IN_ORDER
	};
	enum Spot {
		LEFT = 0,
		RIGHT = 1
	};

	enum Queue {
		NONE = 0,

		PUSH_FRONT = 0b000001,
		PUSH_BACK = 0b000010,

		POP_FRONT = 0b000100,
		POP_BACK = 0b001000,

		LINEAR = 0b000000,
		CIRCULAR = 0b010000,

		FIFO = PUSH_BACK | POP_FRONT,
		FILO = PUSH_BACK | POP_BACK,
		DOUBLE = FIFO | FILO
	};


	constexpr Queue operator|(Queue first, Queue second) {
		return Queue(int(first) | int(second));
	}

	enum Graph {
		DEFAULT =	0b0000,
		DIRECTED =	0b0001,
		WEIGHTED =	0b0010,
	};

	constexpr Graph operator|(Graph first, Graph second) {
		return Graph(int(first) | int(second));
	}
}