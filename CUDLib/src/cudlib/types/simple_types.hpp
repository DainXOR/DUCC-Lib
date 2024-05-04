#pragma once

#include <cstring>

namespace duc {
	template<size_t size>
	struct bytes {
		unsigned char data[size];
		size_t lastSection;
		unsigned char lastBitPos;

		bytes() {
			std::memset(data, 0, size);
			lastSection = 0;
			lastBitPos = 0;
		}
		bytes(const bytes& other) {
			std::memcpy(data, other.data, size);
			lastSection = other.lastSection;
			lastBitPos = other.lastBitPos;
		}
		bytes(const unsigned char* other) {
			std::memcpy(data, other, size);

			lastSection = 0;
			lastBitPos = 0;

			for (size_t i = 0; i < size; i++) {
				if (data[i] != 0) {
					lastSection = i;
					lastBitPos = 0;

					for (size_t j = 0; j < 8; j++) {
						if ((data[i] >> j) & 1) {
							lastBitPos = j;
						}
					}
				}
			}

		}
		bytes(const unsigned char* other, size_t len) {
			std::memcpy(data, other, len);
		}
		bytes(const auto uintValue) {
			unsigned char aux[size] = {};

			for (size_t i = 0; i < size; i++) {
				data[i] = (uintValue >> (i * 8)) & 0xFF;
			}
		}

		unsigned char& operator[](size_t index) {
			return data[index];
		}
		const unsigned char& operator[](size_t index) const {
			return data[index];
		}

		unsigned char& at(size_t index) {
			if (index >= size) {
				throw std::out_of_range("index out of range");
			}

			return data[index];
		}
		const unsigned char& at(size_t index) const {
			if (index >= size) {
				throw std::out_of_range("index out of range");
			}

			return data[index];
		}

		bytes& operator&(const bytes& other) {
			for (size_t i = 0; i < size; i++) {
				data[i] &= other.data[i];
			}

			return *this;
		}
	};

}