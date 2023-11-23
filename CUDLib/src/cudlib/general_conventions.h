#pragma once
//#include <type_traits>
#include <typeinfo>
#include <xutility>

namespace duc::satisfy {
	template<typename buffer>
	concept Iterable = requires(buffer B) {
		std::begin(B);
		std::end(B);
		std::rbegin(B);
		std::rend(B);
		std::cbegin(B);
		std::cend(B);
		std::crbegin(B);
		std::crend(B);

		typename buffer::iterator;
		typename buffer::const_iterator;
		typename buffer::reverse_iterator;
		typename buffer::const_reverse_iterator;
	};
	template<typename buffer>
	concept Indexable = requires(buffer B, int64_t I) {
		B[I];
	};

	template<class container_type>
	concept Container = requires(container_type C, int64_t I) {
		typename container_type::value_type;

		Iterable<container_type>;
		Indexable<container_type>;
	};

	template<typename return_t, typename ...args, template <class, class...> class functor>
	concept Callable = requires(functor<return_t, args...> f, args ...argv) {
		{ f(argv...) } -> std::convertible_to<return_t>;
	};

	template<template <class, auto...> class functor, typename return_t, typename ...args>
	concept ConstexprCallable = requires(functor <return_t, args{}...> f) {
		{ f() } -> std::convertible_to<return_t>;
	};
}