#pragma once
#include <string>

namespace duc {
	enum key_type {
		NUMERIC,
		ALPHABETIC,
		ALPHANUMERIC,
		SYMBOLIC,
		HEXADECIMAL,
		BINARY,
		OCTAL,
		DECIMAL
	};
	enum cypher {
		CAESAR		= key_type::NUMERIC,
		VIGENERE	= key_type::ALPHABETIC,
		ENIGMA		= key_type::ALPHANUMERIC,
		FEISTEL		= key_type::SYMBOLIC,
		DES			= key_type::HEXADECIMAL,
		AES			= key_type::BINARY,
		RC4			= key_type::OCTAL,
		RC5			= key_type::DECIMAL,
		RC6			= key_type::DECIMAL,
		BLOWFISH	= key_type::DECIMAL,
		TWOFISH		= key_type::DECIMAL,
		SERPENT		= key_type::DECIMAL,
		THREEFISH	= key_type::DECIMAL,
		IDEA		= key_type::DECIMAL,
		TEA			= key_type::DECIMAL,
		XTEA		= key_type::DECIMAL,
		XXTEA		= key_type::DECIMAL,
		SALSA20		= key_type::DECIMAL,
		CHACHA20	= key_type::DECIMAL,
		RC4A		= key_type::DECIMAL,
		RC4PLUS		= key_type::DECIMAL,
		RC4DROP		= key_type::DECIMAL,
		RC4FULL		= key_type::DECIMAL,
		RC4HC		= key_type::DECIMAL,

	};

	class reticent {
		cypher _cypher;
		key_type _key_type;

	public:
		bool configure(cypher c, key_type k) noexcept;
		bool restrictValues(size_t minValue, size_t maxValue) noexcept;

		cypher getCypher() const noexcept { return this->_cypher; };
		key_type getKeyType() const noexcept { return this->_key_type; };

		void setCypher(cypher c) noexcept { this->_cypher = c; };
		void setKeyType(key_type k) noexcept { this->_key_type = k; };

		std::string encrypt(std::string text, std::string key);
		std::string decrypt(std::string text, std::string key);

		std::string encrypt(std::string text, std::string key, cypher c);
		std::string decrypt(std::string text, std::string key, cypher c);

		std::string generateKey(key_type type, size_t sizeMin = 1, size_t sizeMax = ~0);

	private:
		std::string createNumericKey(size_t sizeMin = 1, size_t sizeMax = ~0);
		std::string createAlphabeticKey(size_t sizeMin = 1, size_t sizeMax = ~0);
		std::string createAlphanumericKey(size_t sizeMin = 1, size_t sizeMax = ~0);
		std::string createSymbolicKey(size_t sizeMin = 1, size_t sizeMax = ~0);
		std::string createHexadecimalKey(size_t sizeMin = 1, size_t sizeMax = ~0);
		std::string createBinaryKey(size_t sizeMin = 1, size_t sizeMax = ~0);
		std::string createOctalKey(size_t sizeMin = 1, size_t sizeMax = ~0);
		std::string createDecimalKey(size_t sizeMin = 1, size_t sizeMax = ~0);

	};
}


