#pragma once

#include "../utilities/collection_base.h"
#include "nodes.h"


namespace duc::ex {

	template<typename type, class node_type = snode<type>>
	class llist {
	public:

		virtual size_t size() const noexcept = 0;

		virtual bool pushBack(node_type *newNode) = 0;
		virtual bool pushFront(node_type *newNode) = 0;

		virtual bool insert(node_type *newNode, size_t index) = 0;
		virtual bool emplace(type newElement) = 0;

		virtual bool remove(size_t index) = 0;
		virtual bool removeElement(type element) = 0;
		virtual node_type *drop(size_t index) = 0;
		virtual node_type *drop(type element) = 0;

		virtual const node_type *get(size_t index) const = 0;
		virtual node_type *operator[](size_t index) = 0;

		#ifdef _STRING_
		virtual operator std::string() const = 0;
		#endif // _STRING_

		#ifdef _IOSTREAM_
		friend std::ostream &operator<<(std::ostream& os, const llist& ll) {
			return os << std::string(ll);
		}
		#endif // _IOSTREAM_
	};


	template<typename type>
	class sllist : public llist<type> {
		size_t lenght;
		snode<type> *first;
		snode<type> *last;

	public:
		sllist()
			: lenght(0), first(), last() {}
		sllist(snode<type> *firstNode)
			: lenght(1), first(firstNode), last(firstNode) {

			snode<type> *it = this->first->next;
			while (it != nullptr) {
				lenght++;
				it = it->next;
			}

			return;
		}

		size_t size() const noexcept {
			return this->lenght;
		}

		bool pushBack(snode<type> *newNode) {
			if (!this->size()) {
				this->first = newNode;
			}
			else {
				this->last->next = newNode;
			}

			snode<type> *it = newNode;
			while (it->next != nullptr) {
				it = it->next;
				this->lenght++;
			}

			this->last = it;

			this->lenght++;
			return true;
		}
		bool pushFront(snode<type> *newNode) {

			newNode->next = this->first;
			this->first = newNode;

			this->lenght++;
			return true;
		}

		bool insert(snode<type> *newNode, size_t index) {
			if (this->size() >= index) {
				snode<type> *it = this->first;
				snode<type> *prev = nullptr;

				for (int i = 0; i < index - 1; i++) {
					prev = it;
					it = it->next;
				}

				prev->next = newNode;
				newNode->next = it;
				this->lenght++;
			}

			return true;
		}
		bool emplace(type newElement) {
			return this->pushBack(new snode(newElement));;
		}

		bool remove(size_t index) {
			this->drop(index);
			return true;
		}
		bool removeElement(type element) {
			this->drop(element);
			return true;
		}
		snode<type> *drop(size_t index) {
			if (this->size() < index) return this->last;

			snode<type> *it = this->first;
			snode<type> *next = it->next;

			for (int i = 1; i < index; i++) {
				it = it->next;
				next = it->next;
			}

			it->next = next->next;
			this->lenght--;
			return it;
		}
		snode<type> *drop(type element) {
			snode<type> *it = this->first;
			snode<type> *next = it->next;

			while (next != nullptr && next->element != element) {
				it = next;
				next = it->next;
			}

			if (next != nullptr) {
				it->next = next->next;
				this->lenght--;
			}

			return it;
		}

		const snode<type> *get(size_t index) const {
			if (this->size() < index) return this->last;

			snode<type> *it = this->first;
			for (int i = 0; i < index; i++) {
				it = it->next;
			}

			return it;
		}
		snode<type> *operator[](size_t index) {
			if (this->size() < index) return this->last;

			snode<type> *it = this->first;
			for (int i = 0; i < index; i++) {
				it = it->next;
			}

			return it;
		}

		#ifdef _STRING_
		operator std::string() const {
			std::string result = "";
			const snode<type> *it = this->first;

			while (it != nullptr) {
				result += std::to_string(it->element);
				it = it->next;
				result += "->";
			}

			result += "void";
			return result;
		}
		#endif // _STRING_

		~sllist() {}

	private:

	};

	template<typename type>
	class cllist : public llist<type> {
		size_t lenght;
		snode<type> *first;

	public:
		cllist()
			: lenght(0), first() {}
		cllist(snode<type> *firstNode)
			: lenght(1), first(firstNode) {

			snode<type> *it = this->first->next;
			while (it != nullptr) {
				lenght++;
				it = it->next;
			}

			return;
		}

		size_t size() const noexcept {
			return this->lenght;
		}

		bool pushBack(snode<type> *newNode) {
			if (!this->size()) {
				this->first = newNode;
				newNode->next = this->first;
			}
			else {
				snode<type> *it = this->first;
				snode<type> *next = it->next;

				for (int i = 0; next != this->first; i++) {
					it = next;
					next = next->next;
				}

				it->next = newNode;
				newNode->next = this->first;
			}

			this->lenght++;
			return true;
		}
		bool pushFront(snode<type> *newNode) {
			this->insert(newNode, this->size());
			this->first = newNode;

			this->lenght++;
			return true;
		}

		bool insert(snode<type> *newNode, size_t index) {
			index %= this->size() + 1;
			//if (index == 0) {
			//	index = this->size();
			//}

			snode<type> *it = this->first;
			snode<type> *next = it->next;


			for (int i = 1; i < index; i++) {
				it = next;
				next = next->next;
			}

			it->next = newNode;
			newNode->next = next;
			this->lenght++;
			(index == this->size()) && (this->first = newNode);
			return true;
		}
		bool emplace(type newElement) {
			return this->pushBack(new snode(newElement));
		}

		bool remove(size_t index) {
			this->drop(index);
			return true;
		}
		bool removeElement(type element) {
			this->drop(element);
			return true;
		}
		snode<type> *drop(size_t index) {
			snode<type> *it = this->first;
			snode<type> *next = it->next;
			index %= this->size();

			for (int i = 1; i < index; i++) {
				it = it->next;
				next = it->next;
			}

			it->next = next->next;
			this->lenght--;
			return it;
		}
		snode<type> *drop(type element) {
			snode<type> *it = this->first;
			snode<type> *next = it->next;

			while (next->element != element && next != this->first) {
				it = next;
				next = it->next;
			}

			if (next->element == element) {
				it->next = next->next;
				this->lenght--;
			}

			return it;
		}

		const snode<type> *get(size_t index) const {
			snode<type> *it = this->first;
			index %= this->size();

			for (int i = 0; i < index; i++) {
				it = it->next;
			}

			return it;
		}
		snode<type> *operator[](size_t index) {
			snode<type> *it = this->first;
			index %= this->size();

			for (int i = 0; i < index; i++) {
				it = it->next;
			}

			return it;
		}

		#ifdef _STRING_
		operator std::string() const {
			std::string result = "";

			if (this->size()) {
				const snode<type> *it = this->first;

				for (size_t i = 0; i < this->size(); i++) {
					result += std::to_string(it->element);

					it = it->next;
					result += "->";
				}
				result += "...";
			}
			else {
				result += "void";
			}

			return result;
		}
		#endif // _STRING_


		~cllist() {}

	private:

	};

	template<typename type>
	class dllist : public llist<type, dnode<type>> {
		size_t lenght;
		dnode<type> *first;
		dnode<type> *last;

	public:
		dllist()
			: lenght(0), first(nullptr), last(nullptr) {}
		dllist(dnode<type> *firstNode)
			: lenght(1), first(firstNode), last(firstNode) {

			dnode<type> *it = this->first;
			while (it->next != nullptr) {
				lenght++;
				it = it->next;
			}
			this->last = it;

			return;
		}

		size_t size() const noexcept {
			return this->lenght;
		}

		bool pushBack(dnode<type> *newNode) {
			if (!this->size()) {
				this->first = newNode;
			}
			else {
				newNode->back = this->last;
				this->last->next = newNode;
			}

			dnode<type> *it = newNode;
			while (it->next != nullptr) {
				it = it->next;
				this->lenght++;
			}

			this->last = it;

			this->lenght++;
			return true;
		}
		bool pushFront(dnode<type> *newNode) {

			newNode->next = this->first;
			this->first->back = newNode;
			this->first = newNode;

			this->lenght++;
			return true;
		}

		bool insert(dnode<type> *newNode, size_t index) {

			if (index == 0) return this->pushFront(newNode);
			if (index >= this->size()) return this->pushBack(newNode);

			index += 1;

			int iterDirection = ((this->size() - index >= this->size() >> 1) * 2) - 1;
			dnode<type> *it = iterDirection > 0 ? this->first : this->last;

			size_t i = 0;

			if (iterDirection > 0) {
				for (i = 0; i < index - 2; i++, it = it->next);
			}
			else {
				for (i = this->size(); i > index; i--, it = it->back);
				// i = this->size() - i; // Only for benchmark
			}

			newNode->back = it;
			newNode->next = it->next;

			it->next->back = newNode;
			it->next = newNode;

			this->lenght++;

			return true;
		}
		bool emplace(type newElement) {
			return this->pushBack(new dnode(newElement));;
		}

		bool remove(size_t index) {
			this->drop(index);
			return true;
		}
		bool removeElement(type element) {
			this->drop(element);
			return true;
		}
		dnode<type> *drop(size_t index) {
			if (this->size() < index) return this->last;

			int iterDirection = ((this->size() - index >= this->size() >> 1) * 2) - 1;
			dnode<type> *it = iterDirection > 0 ? this->first : this->last;

			size_t i = 0;

			if (iterDirection > 0) {
				for (i = 0; i < index - 2; i++, it = it->next);
			}
			else {
				for (i = this->size(); i > index; i--, it = it->back);
			}

			it = it->next;

			it->back->next = it->next;
			it->next->back = it->back;

			this->lenght--;
			return it;
		}
		dnode<type> *drop(type element) {
			dnode<type> *it = this->first;
			dnode<type> *rit = this->last;

			int who = ((it->element == element) * 2) - rit->element == element;

			while (!(who || it == rit || it->next == rit)) {
				it = it->next;
				rit = rit->back;
				who = ((it->element == element) * 2) - rit->element == element;
			}

			if (who) {
				this->lenght--;
				return who > 0 ? it : rit;
			}

			return nullptr;
		}

		const dnode<type> *get(size_t index) const {
			if (this->size() < index) return this->last;

			dnode<type> *it = this->first;
			for (int i = 0; i < index; i++) {
				it = it->next;
			}

			return it;
		}
		dnode<type> *operator[](size_t index) {
			if (this->size() < index) return this->last;

			dnode<type> *it = this->first;
			for (int i = 0; i < index; i++) {
				it = it->next;
			}

			return it;
		}
		
		#ifdef _STRING_
		operator std::string() const {
			std::string result = "";
			const dnode<type> *it = this->first;

			while (it != nullptr) {
				result += std::to_string(it->element);
				it = it->next;
				result += "<=>";
			}

			result += "void";

			return result;
		}
		#endif // _STRING_

		~dllist() {}

	private:
	};



}