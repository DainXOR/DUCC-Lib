#pragma once
#include <string>
#include <cstdint>

#include<cudlib/utils_declarations.h>
#include <dtmlib/utilities/conventions.h>
//#include <dtmlib/functions/>

namespace duc {
	namespace generator {
		template<size_t minSize, size_t maxSize, class int_t = uint32_t, auto predicate = [](int_t) { return true; } >
		requires(satisfy::UnsignedInteger<int_t>)
		struct numeric {
			using key_type = int_t; 

			constexpr static key_type next(key_type startPoint = 0) noexcept {
				static key_type key = startPoint < minSize ? minSize : startPoint;

				if (key > maxSize) key = minSize;

				if (predicate(key)) return key++;
				else return next(key++);
			}
		};

		

	}

	namespace cypher {
		template<class int_t = uint32_t>
		struct caesar {
			using key_type = int_t;

			static std::string encrypt(std::string text, key_type key) noexcept {
				for (auto& c : text) {
					c += key;
				}
				return text;
			}
			static std::string decrypt(std::string text, key_type key) noexcept {}
		};
	}

	template<class cypher_t, class key_generator_t = generator::numeric>
	requires(std::is_same_v<key_generator_t, void> || std::is_same_v<typename cypher_t::key_type, typename key_generator_t::key_type>)
	class reticent {
	private:
		class builder;
		using key_t = typename cypher_t::key_type;

		const cypher_t cypher;
		const key_t key;

	public:
		static builder create() const noexcept {
			return builder();
		}

		cypher_t getCypher() const noexcept { return this->cypher; };
		key_t getKey() const noexcept { return this->key; };

		std::string encrypt(std::string text);
		std::string decrypt(std::string text);


	private:
		class builder {
			reticent* reticent;

		public:
			builder() noexcept;
			builder(reticent* reticent) noexcept;

			builder& restrictValues(size_t minValue, size_t maxValue) noexcept;

			builder& setCypher(cypher_t cypher) noexcept;
			builder& setKey(key_t key) noexcept;

			std::string generateKey(key_t type, size_t sizeMin = 1, size_t sizeMax = ~0);

		}

	public:
	};
}


