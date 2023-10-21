#pragma once
#include <vector>

#include <utilities/conventions.h>
#include "../utilities/traits.h"

#include "nodes.h"


namespace duc::ex {

	template<typename type, size_t branches>
	class tree {
	protected:
		using node_type = mnode<type, branches>;

		node_type *_root = nullptr;
		size_t _depth = 0;
		size_t _lenght = 0;

	public:
		tree(node_type *root = tree::createNode(0)) {
			this->_root = root;
			for (size_t i = 0; i < branches; i++) {
				this->_root->childs[i] = nullptr;
			}

			this->_depth++;
			this->_lenght++;
		}

		node_type *begin() { return this->_root; }
		static node_type *createNode(type value) {
			node_type *n = new node_type{};
			n->element = value;
			return n;
		}

		constexpr size_t branchesPerNode() const noexcept { return branches; };

		size_t depth() const noexcept { return this->_depth; };
		size_t size() const noexcept { return this->_lenght; };

		std::vector<node_type *> getAsArray(traits::Traverse order) {

			return [this, &order]() {
				switch (order) {
					case traits::Traverse::PRE_ORDER: return this->getPreOrder();
					case traits::Traverse::POST_ORDER: return this->getPostOrder();
					case traits::Traverse::IN_ORDER: return this->getInOrder();
					default: return std::vector<node_type *>(this->size());
				}
			}();
		}
		std::vector<node_type *> getPreOrder() {
			std::vector<node_type *> elements;

			elements.push_back(this->begin());
			this->getPreOrder(elements, this->begin()->getChild(0));
			this->getPreOrder(elements, this->begin()->getChild(1));

			return elements;
		}
		std::vector<node_type *> getPostOrder() {
			std::vector<node_type *> elements;

			this->getPostOrder(elements, this->begin()->getChild(0));
			this->getPostOrder(elements, this->begin()->getChild(1));
			elements.push_back(this->begin());

			return elements;
		}
		std::vector<node_type *> getInOrder() {
			std::vector<node_type *> elements;

			this->getInOrder(elements, this->begin()->getChild(0));
			elements.push_back(this->begin());
			this->getInOrder(elements, this->begin()->getChild(1));

			return elements;
		}

		template<satisfy::Integer ...arg_t>
		bool insert(node_type *newNode, size_t head, arg_t...order) {
			return this->insert(newNode, this->begin(), head, order...);
		};
		template<satisfy::Integer ...arg_t>
		bool insert(const type &newElement, size_t head, arg_t...order) {
			node_type *newNode = new node_type{};
			newNode->element = newElement;

			return this->insert(newNode, head, order...);
		};
		template<satisfy::Integer ...arg_t>
		bool insert(type &&newElement, size_t head, arg_t...order) {
			node_type *newNode = new node_type{};
			newNode->element = newElement;

			return this->insert(newNode, head, order...);
		};

		template<std::size_t elems>
		bool insert(node_type *newNode, const std::array<size_t, elems> &indexes) {
			return this->insertIndexSeq(newNode, indexes, std::make_index_sequence<elems>{});
		};
		template<std::size_t elems>
		bool insert(const type &newElement, const std::array<size_t, elems> &indexes) {
			node_type *newNode = new node_type{};
			newNode->element = newElement;

			return this->insert(newNode, indexes);
		};
		template<std::size_t elems>
		bool insert(type &&newElement, const std::array<size_t, elems> &indexes) {
			node_type *newNode = new node_type{};
			newNode->element = newElement;

			return this->insert(newNode, indexes);
		};

	protected:

		void getPreOrder(std::vector<node_type *> &buffer, node_type *node) {
			if (node == nullptr) {
				return;
			}

			buffer.push_back(node);
			this->getPreOrder(buffer, node->getChild(0));
			this->getPreOrder(buffer, node->getChild(1));
		}
		void getPostOrder(std::vector<node_type *> &buffer, node_type *node) {
			if (node == nullptr) {
				return;
			}

			this->getPostOrder(buffer, node->getChild(0));
			this->getPostOrder(buffer, node->getChild(1));
			buffer.push_back(node);
		}
		void getInOrder(std::vector<node_type *> &buffer, node_type *node) {
			if (node == nullptr) {
				return;
			}

			this->getInOrder(buffer, node->getChild(0));
			buffer.push_back(node);
			this->getInOrder(buffer, node->getChild(1));
		}

		template<std::size_t N, std::size_t ... Is>
		bool insertIndexSeq(node_type *newNode, const std::array<size_t, N> & indexes, std::index_sequence<Is...> const &) {
			return this->insert(newNode, this->begin(), indexes[Is]...);
		}

		template<satisfy::Integer ...arg_t>
		bool insert(node_type *newNode, node_type *node, size_t head, arg_t...order) {
			if (node == nullptr || node->getChild(head) == nullptr)
				return false;

			return this->insert(newNode, node->getChild(head), order...);
		};
		template<>
		bool insert(node_type *newNode, node_type *node, size_t tail) {
			if (node->getChild(tail) == nullptr) {
				bool result = node->insertNode(newNode, tail);
				this->_lenght += result;
				return result;
			}

			return false;
		};

		bool remove(size_t index) {};
		bool removeElement(type element) {};
		node_type *drop(size_t index) {};
		node_type *drop(type element) {};

		const node_type *get(size_t index) const {};
		node_type *operator[](size_t index) {};

	public:

	};

	template<typename type>
	class bi_tree : public tree<type, 2> {
	protected:
		using node_type = mnode<type, 2>;
		static constexpr size_t branches = 2;

	public:
		bi_tree() {
			this->_root = new node_type{};
			for (size_t i = 0; i < branches; i++) {
				this->_root->childs[i] = nullptr;
			}

			this->_depth++;
			this->_lenght++;
		}

		bi_tree(node_type *root) {
			this->_root = root;
			for (size_t i = 0; i < branches; i++) {
				this->_root->childs[i] = nullptr;
			}

			this->_depth++;
			this->_lenght++;
		}


	};
};
