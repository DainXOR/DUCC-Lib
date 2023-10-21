#pragma once

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

		static constexpr size_t nodeCount = child_count;

		mnode *getChild(size_t nodeNumber) {
			#ifndef NDEBUG
			//static_assert(nodeCount > nodeNumber, "Node outside of range.");
			#endif // DEBUG

			return this->childs[nodeNumber];
		}

		bool insertNode(mnode *newNode, size_t nodeNumber) {
			#ifndef NDEBUG
			//static_assert(nodeCount > nodeNumber, "Node outside of range.");
			#endif // DEBUG

			bool result = this->childs[nodeNumber] == nullptr;

			this->childs[nodeNumber] = result ? newNode : this->childs[nodeNumber];
			return result;
		}
	};

}

