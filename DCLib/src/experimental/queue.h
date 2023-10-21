#pragma once
#include "../utilities/collection_base.h"
#include "../utilities/traits.h"

namespace duc::ex {

	template<typename type, traits::Queue traits>
	class queue_base : protected collection<type> {

	public:
		virtual inline constexpr traits::Queue getTraits() const noexcept { return traits; }

		virtual bool addAll(const collection<type> &element) = 0;
		
		virtual bool enqueue(type element) = 0;
		virtual bool dequeue(type element) = 0;
	};

	template<typename type>
	class queue : queue_base<type, traits::Queue::FIFO> {
	public:
		bool addAll(const collection<type> &element) {

		}
	};

	template<typename type>
	class stack : queue_base<type, traits::Queue::FILO> {

	};

	template<typename type>
	class cqueue : queue_base<type, traits::Queue::FIFO | traits::Queue::CIRCULAR> {

	};

	template<typename type>
	class pqueue : queue_base<type, traits::Queue::POP_FRONT> {

	};

	template<typename type>
	class dqueue : queue_base<type, traits::Queue::DOUBLE> {};
}