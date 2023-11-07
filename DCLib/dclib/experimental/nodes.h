#pragma once
#include <map>

#include <macro_tools.h>
#include <simple_structures.h>

namespace duc::ex {

	template<typename elem_type>
	struct node {
		elem_type element;

		node *getChild(size_t nodeNumber) {
			return nullptr;
		}

		bool insertNode(node *newNode) {
			return false;
		}
	};

	template<typename elem_type>
	struct snode : public node<elem_type>{
		snode *next = nullptr;
		static constexpr size_t node_count = 1;

		snode *getChild(size_t nodeNumber) {
			return nodeNumber == 0 ? this->next : nullptr;
		}

		bool insertNode(snode *newNode) {
			bool result = this->next == nullptr;
			this->next = result ? newNode : this->next;
			return result;
		}
	};

	template<typename elem_type>
	struct dnode : public node<elem_type> {
		dnode *first = nullptr;
		dnode *second = nullptr;

		static constexpr size_t node_count = 2;

		dnode *getChild(size_t nodeNumber) {
			return node_count > nodeNumber ? nodeNumber == 0 ? this->first : this->second : nullptr;
		}

		bool insertNode(dnode *newNode, bool insertRight = false) {
			bool result = false;
			result = insertRight ? this->insertRight(newNode) : this->insertLeft(newNode);
			return result;
		}
		bool insertLeft(dnode *newNode) {
			bool result = this->first == nullptr;
			this->first = result ? newNode : this->first;
			return result;
		}
		bool insertRight(dnode *newNode) {
			bool result = this->second == nullptr;
			this->second = result ? newNode : this->second;
			return result;
		}

	};

	template<typename elem_type, size_t child_count>
	struct mnode : public node<elem_type> {
		mnode *childs[child_count] = {};

		static constexpr size_t connectCount = child_count;

		mnode *getChild(size_t nodeNumber) {
			#ifndef NDEBUG
			//static_assert(childCount > nodeNumber, "Node outside of range.");
			#endif // DEBUG

			return this->childs[nodeNumber];
		}

		bool insertNode(mnode *newNode, size_t nodeNumber) {
			#ifndef NDEBUG
			//static_assert(childCount > nodeNumber, "Node outside of range.");
			#endif // DEBUG

			bool result = this->childs[nodeNumber] == nullptr;

			this->childs[nodeNumber] = result ? newNode : this->childs[nodeNumber];
			return result;
		}
	};

	template<typename elem_type, typename id_t = uint32_t>
	struct wnode {
	public:
		using id_type = id_t;
		using element_type = elem_type;
		using weight_type = size_t;
		using connections_map = std::map<id_type, weight_type>;

		elem_type element;
		const id_type id;
		size_t connectionCount;
		connections_map connections;

	public:
		wnode(elem_type element) noexcept
			: element(element), id(wnode::nextID()), connectionCount(0), connections({}) {}

		id_type getID() const noexcept { return this->id; }
		elem_type getElement() const noexcept { return this->element; }
		size_t getConnectionCount() const noexcept { return this->connectionCount; }
		const connections_map &getConnections() const noexcept { return this->connections; }

		bool connect(id_type nodeID, weight_type weight) {
			if (this->connections.contains(nodeID)) return false;

			bool result = this->connections.insert({ nodeID, weight }).second;
			return result && ++this->connectionCount;
		}
		bool disconnect(id_type nodeID) {
			return this->connections.erase(nodeID);
		}
		bool changeWeight(id_type nodeID, weight_type newWeight) {
			auto result = this->connections.find(nodeID);
			if (result != this->connections.end()) {
				result->second = newWeight;
				return true;
			}
			return false;
		}

	private:
		DUC_RNODISCARD inline static id_type nextID() noexcept {
			static id_type ID = 0;
			return ++ID;
		}
	};
}

