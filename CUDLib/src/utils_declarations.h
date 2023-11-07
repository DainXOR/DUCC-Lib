#pragma once
#include "general_conventions.h"

#include <stdint.h>

namespace duc::util {

	template<class t>
	struct type_info;

	template<auto v>
	struct var_info;

	template<auto ...v>
	struct expansion;

	template<class, auto...>
	struct yes;
	template<class, auto...>
	struct no;
	template<class, int64_t number>
	struct is_prime;

	namespace {
		template<size_t count, auto v0, auto ...v>
		struct expand_helper : expand_helper<count - 1, v0, v0, v...> {};

		template<auto v0, auto ...v>
		struct expand_helper<0, v0, v...> : expansion<v...> {};

		template<int64_t end, int64_t begin, int64_t step, template<class, auto...> class predicate, int64_t n0, int64_t ...n>
			requires (step != 0 && satisfy::ConstexprCallable<predicate, bool, int64_t>)
		constexpr auto sequenceGenerator();

		template<auto ...v>
		constexpr duc::util::expansion<v...> unrollExpansions(duc::util::expansion<v...> ex);
		template<auto ...iv, auto...ov>
		constexpr auto unrollExpansions(duc::util::expansion<iv...>, duc::util::expansion<ov...>, auto ...v);

		template<int count, auto ... args>
		constexpr auto origin();
		template<int count, auto ... args, auto ... args2>
		constexpr auto replicator(duc::util::expansion<args...> o, duc::util::expansion<args2...> r);

		template<int64_t number>
		constexpr bool isPrime();

		template<auto ...I>
		constexpr bool isPrime(int64_t num, expansion<I...>);
	}

	template<int64_t end, int64_t begin = 0, int64_t step = 1, template<class, auto...> class predicate = yes>
	static constexpr expansion sequence = sequenceGenerator<end, begin, step, predicate, begin>();

	template<int64_t end, int64_t begin = 2, int64_t step = 1>
	static constexpr expansion primeSequence = sequence<end, begin, step, is_prime>;


	template<size_t count, auto v0>
	static constexpr expansion expand = expand_helper<count, v0>{};

	template<size_t count, auto v0, auto ...v>
	static constexpr expansion clone = expand < count, expansion<v0, v...>{} > ;

	template<size_t count, auto v0, auto ...v>
	static constexpr expansion replicate = origin<count, v0, v...>();

	template<size_t count, auto ...v>
	static constexpr expansion echo = unrollExpansions(duc::util::expansion<>{}, duc::util::expand<count, v>...);


	template<int64_t end, int64_t begin = 0, int64_t step = 1, template<class, auto...> class predicate = yes>
		requires (step != 0 && satisfy::ConstexprCallable<predicate, bool, int64_t>)
	class sequence_array;
}
