#pragma once
#include <iostream>
#include <array>
#include <queue>

#include <cudlib/simple_structures.h>

namespace duc::ex::alg {

    template <class compare_t, template <class> class comp = std::less>
    struct compare_first {
        [[nodiscard]]
        constexpr bool operator()(const auto& left, const auto& right) const noexcept {
            return comp<compare_t>{}(left.first, right.first);
        }
    };
    template <class compare_t, template <class> class comp = std::less>
    struct compare_second {
        [[nodiscard]]
        constexpr bool operator()(const auto& left, const auto& right) const noexcept {
            return comp<compare_t>{}(left.second, right.second);
        }
    };
	
    template<class graph_t>
	struct dijkstra {
        using id_t = typename graph_t::id_t;
        using weight_t = typename graph_t::weight_t;
        using route_t = typename graph_t::route_t;

        using connection_data = duc::pair_any<id_t, weight_t>;
        using visit_queue = std::priority_queue<connection_data, std::vector<connection_data>, compare_second<weight_t, std::greater>>;

        graph_t &graph;
        weight_t maxWeight;

        dijkstra(graph_t& newGraph, weight_t weight = ~0)
            : graph(newGraph), maxWeight(weight) {}

        void setGraph(graph_t& newGraph) {
            this->graph = newGraph;
            this->maxWeight = ~0;
        }
        void setWeightToBeat(weight_t weight) {
            this->maxWeight = weight;
        }

        route_t search(id_t startID, id_t endID) {
            if (!this->graph.contains(startID) || !this->graph.contains(endID)) return {};

            return this->search(connection_data{ startID, 0 }, endID, route_t{});
        }

        route_t search(connection_data visit, id_t endID, route_t currentRoute) {
            currentRoute.first.push_back(visit.first);
            currentRoute.second += visit.second;

            if (visit.first == endID && this->maxWeight > currentRoute.second) {
                currentRoute.first.erase(currentRoute.first.begin());
                this->maxWeight = currentRoute.second;
                return currentRoute;
            }

            visit_queue nodeQueue = {};

            for (auto &[connectionsID, weight] : this->graph.getConnectionsOf(visit.first)) {
                bool dontAdd = currentRoute.second + weight > this->maxWeight;
                if (dontAdd) continue;
                for (id_t id : currentRoute.first) {
                    dontAdd |= connectionsID == id;
                }
                if(!dontAdd) nodeQueue.push({ connectionsID, weight });
            }

            route_t finalRoute = { {}, this->maxWeight };

            for (; !nodeQueue.empty(); nodeQueue.pop()) {
                connection_data next = nodeQueue.top();

                route_t updatedRoute = this->search(next, endID, currentRoute);

                if (updatedRoute.second < finalRoute.second && 
                    updatedRoute.first[updatedRoute.first.size() - 1] == endID) {

                    finalRoute = updatedRoute;
                }
            }

            return finalRoute;
        }
	};
}

int mainDijkstra() {

    return 0;
}