#pragma once
#include <concepts>

#include <utilities/conventions.h>

namespace duc::satisfy {
	template<class node_t>
	concept WeightedNode = requires (node_t node) {
		UnsignedInteger<typename node_t::id_type>;
		typename node_t::element_type;
		UnsignedInteger<typename node_t::weight_type>;
		typename node_t::connection_type;

		{ node.getID() } -> std::same_as<typename node_t::id_type>;
		{ node.getElement() }  -> std::same_as<typename node_t::element_type>;
		{ node.getConnectionCount() }  -> std::convertible_to<size_t>;
		{ node.getConnections() } -> std::ranges::range;

		node.connect(typename node_t::id_type(0), typename node_t::weight_type(0));
		node.disconnect(typename node_t::id_type(0));
		node.changeWeight(typename node_t::id_type(0), typename node_t::weight_type(0));

	};
}