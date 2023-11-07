#pragma once
#include <iostream>
#include <array>

#include <utilities/conventions.h>

namespace duc::ex::alg {
	
    template<class graph_t>
	struct dijkstra {
        using id_t = typename graph_t::node_id_type;
        using weight_t = typename graph_t::node_weight_type;

        graph_t graph;
        weight_t maxWeight;

        void setGraph(const graph_t& newGraph) {
            this->graph = newGraph;
            this->maxWeight = ~0;
        }
        void weightToBeat(weight_t weight) {
            this->maxWeight = weight;
        }

        auto search(id_t startID, id_t endID) {
            typename graph_t::route_type route = {};
            startID == endID ? route.push_back(endID) : route.clear();

            bool shouldSearch = this->graph.getNode(startID) &&
                                this->graph.getNode(endID) &&
                                !this->graph.getNode(endID)->getConnections().empty();

            return shouldSearch ?
                        this->search(startID, endID, std::vector<id_t>{}) :
                        duc::pair_any{ route, weight_t(0) };
        }

        auto search(id_t startID, id_t endID, std::vector<id_t> nodesVisited) {
            weight_t newWeight = 0;
            typename graph_t::route_type route = {};
            typename graph_t::route_type newRoute = {};
            const auto &connections = this->graph.getNode(startID)->getConnections();

            for (const auto &[connectionID, connectionWeight] : connections) {
                bool notVisited = true;

                if (connectionID == endID) {
                    route.push_back(connectionID);
                    newWeight += connectionWeight;
                    return duc::pair_any{ route, newWeight };
                }
                for(auto n : nodesVisited) {
                    if (n == connectionID) {
                        notVisited = false;
                        break;
                    }
                }

                if (notVisited) {
                    nodesVisited.push_back(startID);
                    route.push_back(connectionID);
                    newWeight += connectionWeight;
                    auto [currentRoute, currentWeight] = this->search(connectionID, endID, nodesVisited);
                    //std::vector<int>{};

                    if (this->maxWeight > (newWeight + currentWeight) && currentRoute.back() == endID) {
                        this->maxWeight = newWeight + currentWeight;
                        route.append_range(currentRoute);
                        newWeight = 0;
                    }
                }
            }
            return duc::pair_any{ route, newWeight };
        }
        auto searchForAll(id_t sourceID) {
            typename graph_t::node_routes_type routes = {};
            this->graph;
        }
        auto searchForAllNodes() {
            typename graph_t::web_routes_type routes = {};
            this->graph;

        }
	};
}

int mainDijkstra() {

    return 0;
}