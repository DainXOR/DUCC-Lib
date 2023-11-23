#pragma once
#include <vector>
#include <array>

namespace duc::ex {

	namespace TEMP {
		template<class id_t>
		[[nodiscard]] id_t createNodeID() noexcept {
			static id_t IDCount = {};
			return ++IDCount;
		}
	}

	template<typename element_type, size_t siblingCount = 0, class id_type = uint16_t>
	struct node {
		using id_t = id_type;
		using element_t = element_type;

		element_t element;
		std::array<node *, siblingCount> siblings = {};
		const id_t id = TEMP::createNodeID<id_t>();
		
		constexpr size_t maxSiblings() { return siblingCount; }
		constexpr size_t getSiblingCount() const noexcept { return siblingCount; }
		constexpr id_t getID() const noexcept { return this->id; }
		constexpr element_t getElement() const noexcept { return this->element; }

		constexpr node *getSibling(size_t index) {
			return nullptr;
		}
		constexpr node *setSibling(size_t index, node *newNode) {
			return nullptr;
		}

		constexpr bool insertAt(size_t index, node *newNode) {
			return false;
		}
		constexpr bool emplaceAt(element_t element) {
			return false;
		}
	};

	template<typename element_type>
	struct snode : public node<element_type, 1>{
		using element_t = element_type;

		std::array<snode *, 1> siblings = {};

		snode *getSibling() {
			return this->siblings[0];
		}
		snode *getSibling(size_t index) {
			return index == 0 ? this->siblings[0] : nullptr;
		}
		void setSibling(size_t index, snode *newNode) {
			this->siblings[index] = newNode;
			return;
		}

		bool insertAt(size_t index, snode *newNode) {
			bool result = this->siblings[0] == nullptr;
			this->siblings[0] = result ? newNode : this->siblings[0];
			return result;
		}
		constexpr bool emplaceAt(size_t index, element_t element) {
			return this->insertAt(index, new snode{ element });
		}
	};

	template<typename element_type>
	struct dnode : public node<element_type, 2> {
		using element_t = element_type;
		std::array<dnode *, 2> siblings = {};

		dnode *getSibling(size_t index) {
			return this->siblings[index];
		}
		void setSibling(size_t index, dnode *newNode) {
			this->siblings[index] = newNode;
			return;
		}

		bool insertAt(size_t index, dnode *newNode) {
			bool result = this->siblings[index] == nullptr;
			this->siblings[index] = result ? newNode : this->siblings[index];
			return result;
		}
		constexpr bool emplaceAt(size_t index, element_t element) {
			return this->insertAt(index, new dnode{ element });
		}
	};

	template<typename element_type, size_t siblingCount>
	struct mnode : public node<element_type, siblingCount> {
		using element_t = element_type;

		std::array<mnode *, siblingCount> siblings = {};

		mnode *getSibling(size_t index) {
			return this->siblings[index];
		}
		void setSibling(size_t index, mnode *newNode) {
			this->siblings[index] = newNode;
			return;
		}

		bool insertAt(size_t index, mnode *newNode) {
			bool result = this->siblings[index] == nullptr;
			this->siblings[index] = result ? newNode : this->siblings[index];
			return result;
		}
		constexpr bool emplaceAt(size_t index, element_t element) {
			return this->insertAt(index, new mnode{ element });
		}
	};

	template<typename element_type>
	struct xnode : public node<element_type, 0> {
		using element_t = element_type;

		std::vector<xnode *> siblings = {};

		constexpr size_t getSiblingCount() const noexcept { return this->siblings.size(); }

		xnode *getSibling(size_t index) { return this->siblings[index]; }
		std::vector<xnode *> getSiblings() { return this->siblings; }

		void setSibling(size_t index, xnode *newNode) {
			if (this->siblings.size() <= index) {
				this->siblings.resize(index + 1);
			}

			this->siblings[index] = newNode;
			return;
		}

		void insert(xnode *newNode) {
			this->siblings.push_back(newNode);
			return;
		}
		constexpr void emplace(element_t element) {
			this->insert(new xnode{ element });
			return;
		}

		bool insertAt(size_t index, xnode *newNode) {
			if (index >= this->siblings.size() || this->siblings[index] == nullptr) {
				this->setSibling(index, newNode);
				return true;
			}

			return false;
		}
		constexpr bool emplaceAt(size_t index, element_t element) {
			return this->insertAt(index, new xnode{ element });
		}
	};
}

