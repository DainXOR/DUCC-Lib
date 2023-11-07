#pragma once
#include <unordered_map>
#include <map>
#include <vector>

#include "../utilities/conventions.h"
#include "../structures/collections.h"
#include "nodes.h"

namespace duc::ex {

	template<typename type, satisfy::WeightedNode node_t = wnode<type>>
	class graph {
	public:
		using node_type = node_t;
		using node_id_type = typename node_type::id_type;
		using node_weight_type = typename node_type::weight_type;

		using connection_type = duc::triplet_any<node_id_type, node_id_type, size_t>;
		using web_type = std::map<node_id_type, node_type *>;

		using route_type = std::vector<node_id_type>;
		using node_routes_type = std::unordered_map<node_id_type, route_type>;
		using web_routes_type = std::unordered_map<node_id_type, node_routes_type>;

	public:
		web_type nodes;
		web_routes_type routes;
		

	public:
		node_type* getNode(node_id_type id) const noexcept {
			auto result = nodes.find(id);
			return result != nodes.end() ? result->second : nullptr;
		}
		std::vector<node_type> getNodes() const noexcept {
			std::vector<node_type> n;
			n.reserve(this->nodes.size());

			for (auto [key, value] : this->nodes) {
				n.push_back(*value);
			}
			return n;
		}
		std::vector<uint64_t> getNodesIDs() const noexcept {
			std::vector<uint64_t> ids;
			ids.reserve(this->nodes.size());

			for (auto [key, value] : this->nodes) {
				ids.push_back(key);
			}
			return ids;
		}
		web_routes_type getAllRoutes() { return this->routes; }
		node_routes_type getRoutesOf(node_id_type id) { return this->routes[id]; }

		bool createNode(node_type *node) noexcept {
			return this->nodes.insert({ node->getID(), node }).second;
		}
		template<typename ...args_t>
		bool emplaceNode(args_t &&... argv) noexcept {
			node_type * newNode = new node_type{ std::forward<args_t>(argv)... };
			bool result = newNode != nullptr;
			return result && this->createNode(newNode);
		}
		template<bool bidirectional = true>
		bool createConnection(connection_type connection) {
			return this->createConnection<bidirectional>(
				connection.first, 
				connection.second, 
				connection.third);
		}
		template<bool bidirectional = true>
		bool createConnection(node_id_type id1, node_id_type id2, size_t weight) {
			if (this->nodes.contains(id1) && this->nodes.contains(id2)) {

				this->nodes[id1]->connect(id2, weight);
				this->createSimpleRoute(id1, id2);

				if constexpr (bidirectional) {
					this->nodes[id2]->connect(id1, weight);
					this->createSimpleRoute(id2, id1);
				}

				//this->optimizeRoutes();
				return true;
			}
			return false;
		}

		bool createSimpleRoute(node_id_type id1, node_id_type id2) {
			this->routes[id1][id2] = route_type{id2};
			return true;
		}
		bool createRoute(node_id_type id1, node_id_type id2) {
			this->routes[id1][id2] = this->findRoute(id1, id2);
		}
		
		route_type findRoute(node_id_type begin, node_id_type end) {
			auto connections = this->getNode(begin)->getConnections();
			route_type path = {};



			path.push_back(end);
			return path;
		}
		bool updateRoutes(){

			return false;
		}
		
		template<template <class> class algorithm>
		web_routes_type optimizeRoutes() {
			//algorithm<duc::util::type_of<this>> alg;
			return web_routes_type{};
		}
		bool rewireGraph() {
			return false;
		}
	};
}


