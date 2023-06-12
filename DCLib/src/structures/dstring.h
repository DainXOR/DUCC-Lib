#pragma once

template<size_t size_>
class dstring {
public:
	const char buffer[size_];

	constexpr size_t size() { return size_; }

	template<size_t otherSize>
	const char* operator+(dstring<otherSize> other) {
		const char* newString = new char[this->size() + other.size()];

		// Make copy
		newString[0] = this->buffer;
		newString[this->size()] = other.buffer;

		return newString;
	}
};

template<>
class dstring<0> {
public:
	const char* buffer;
};
