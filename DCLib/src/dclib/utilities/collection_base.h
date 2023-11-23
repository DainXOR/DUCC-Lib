#pragma once

namespace duc {

	template<typename type>
	class collection {
	public:

		virtual size_t size() const noexcept = 0;

		virtual bool pushBack(const type &element) noexcept = 0;
		virtual bool pushBack(type &&element) noexcept = 0;
		virtual bool pushFront(const type &element) noexcept = 0;
		virtual bool pushFront(type &&element) noexcept = 0;

		virtual bool insert(type element, size_t index) noexcept = 0;

		//template<typename ...arg_t>
		//virtual bool emplaceBack(arg_t ...args) noexcept = 0;
		//template<typename ...arg_t>
		//virtual bool emplaceFront(arg_t ...args) noexcept {};
		//template<typename ...arg_t>
		//virtual bool emplaceAt(size_t index, arg_t ...args) noexcept {};

		virtual bool popBack() noexcept = 0;
		virtual bool popFront() noexcept = 0;

		virtual type &dropBack() noexcept = 0;
		virtual type &dropFront() noexcept = 0;

		virtual type &remove(size_t index) noexcept = 0;
		virtual bool eliminate(size_t index) noexcept = 0;

		virtual type &get(const type &element) noexcept = 0;
		virtual size_t indexOf(const type &element) const noexcept = 0;

		virtual const type &at(size_t index) const noexcept = 0;
		virtual type &operator[](size_t index) = 0;

		#ifdef _STRING_
		virtual operator std::string() const = 0;

		#ifdef _IOSTREAM_
		friend std::ostream &operator<<(std::ostream &os, const collection &c) {
			return os << std::string(c);
		}
		#endif // _IOSTREAM_
		#endif // _STRING_

		#ifdef _DUC_SSTRING_
		virtual operator duc::sstring() const = 0;

		#ifdef _IOSTREAM_
		friend std::ostream &operator<<(std::ostream &os, const linked_list &ll) {
			return os << duc::sstring(ll);
		}
		#endif // _IOSTREAM_
		#endif // _STRING_
	};
}