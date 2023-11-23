#pragma once
#include <unordered_map>
#include <map>
#include <vector>

#include <cudlib/simple_structures.h>

#include "../structures/collections.h"
#include "../utilities/traits.h"

#include "nodes.h"

namespace duc::ex {

	template<typename type, traits::Graph traits = traits::Graph::DEFAULT, template<class> class node_type = xnode>
	class graph {
	public:
		using node_t = node_type<type>;
		using id_t = typename node_t::id_t;
		using weight_t = uint16_t;

		using path_t = std::vector<id_t>;
		using route_t = duc::pair_any<path_t, weight_t>;
		using routes_map_t = std::map<id_t, route_t>;

		using connection_t = duc::pair_any<id_t, weight_t>;
		using web_t = std::map<id_t, duc::pair_any<node_t *, routes_map_t>>;

	public:
		web_t nodes;
		size_t nodeCount;
		
	public:
		constexpr traits::Graph getTraits() const noexcept { return traits; }
		constexpr bool is(traits::Graph trait) { return traits & trait; }
		size_t getSize() const noexcept { return this->nodeCount; }

		node_t* getNode(id_t id) const noexcept {
			auto result = this->nodes.find(id);
			return result != this->nodes.end() ? result->second.first : nullptr;
		}
		std::vector<node_t *> getNodes() const noexcept {
			std::vector<node_t *> n;
			n.reserve(this->nodes.size());

			for (auto &[id, pair] : this->nodes) {
				n.push_back(pair.first);
			}
			return n;
		}
		std::vector<id_t> getNodesIDs() const noexcept {
			std::vector<id_t> ids;
			ids.reserve(this->nodes.size());

			for (auto [id, pair] : this->nodes) {
				ids.push_back(id);
			}
			return ids;
		}

		routes_map_t getRoutesOf(id_t id) { return this->nodes[id].second; }

		std::map<id_t, std::vector<connection_t>> getConnections() {
			std::map<id_t, std::vector<connection_t>> connectionsMap = {};
			for (auto& [id, pair] : this->nodes) {
				std::vector<connection_t> nodeConnections = {};
				for (auto& [destID, route] : pair.second) {
					if (route.first[0] == destID) {
						nodeConnections.push_back(connection_t{ destID, route.second });
					}
				}
				connectionsMap.insert({ id, nodeConnections });
			}
			return connectionsMap;
		}
		std::vector<connection_t> getConnectionsOf(id_t id){
			auto connections = this->getConnections();
			auto result = connections.find(id);
			return result != connections.end() ? result->second : std::vector<connection_t>{};
		}

		bool contains(id_t id) const noexcept {
			return this->nodes.contains(id);
		}

		bool insert(node_t *node) noexcept {
			if (this->contains(node->getID())) {
				return false;
			}
			
			return this->nodes.insert({
						node->getID(),
						duc::pair_any{ node, routes_map_t{} } }).second;
				
		}
		bool emplace(type&& element) noexcept {
			node_t * newNode = new node_t{ element };
			bool result = newNode != nullptr;
			return result && this->insert(newNode);
		}
		
		bool createConnection(id_t id1, id_t id2, weight_t weight = 0) {
			if (this->contains(id1) && this->contains(id2)) {

				this->getNode(id1)->insert(this->getNode(id2));
				this->nodes[id1].second[id2] = route_t{ path_t{id2}, weight };

				if constexpr (!(traits & traits::Graph::DIRECTED)) {
				 	this->getNode(id2)->insert(this->getNode(id1));
					this->nodes[id2].second[id1] = route_t{ path_t{id1}, weight };
				 }
				 
				 //this->optimizeRoutes();
				 return true;
			}
			return false;
		}
		bool createRoute(id_t id1, id_t id2) {
			// this->routes[id1][id2] = this->findRoute(id1, id2);
			return false;
		}
		
		route_t findRoute(id_t begin, id_t end) {
			auto connections = this->getNode(begin)->getConnections();
			route_t path = {};



			path.push_back(end);
			return path;
		}
		bool updateRoutes(){

			return false;
		}
		
		template<template <class> class algorithm>
		web_t optimizeRoutes() {
			//algorithm<duc::util::type_of<this>> alg;
			return web_t{};
		}
		bool rewireGraph() {
			return false;
		}
	};
}


