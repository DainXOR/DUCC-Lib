#pragma once

#include <vector>
#include <functional>

#include "simple_structures.h"

namespace duc {
	namespace flow {

		template<bool expresion, class true_type, class false_type>
		struct if_t {
			using type = false_type;
		};
		template<class true_type, class false_type>
		struct if_t<true, true_type, false_type> {
			using type = true_type;
		};


		template<bool expresion, auto true_value, auto false_value>
		struct if_v {
			static constexpr auto value = false_value;
		};
		template<auto true_value, auto false_value>
		struct if_v<true, true_value, false_value> {
			static constexpr auto value = true_value;
		};

		
		template<class value_type>
		struct match {
			using callback_t = std::function<void()>;

			const value_type &_value;
			bool _fallthrough;
			callback_t _defaultCallback;
			std::vector<callback_t> _actions;

			bool _keepGoing;
			uint8_t _max;
			uint8_t _min;
			uint8_t _jump;
			uint64_t _pattern;
			uint8_t _remaining;

			/*
			* Add selector conditions:
			* - all()		// Default
			* - first()
			* - last()
			* - atLeast(n)
			* - atMost(n)
			* - exactly(n)
			* - every(n)
			*/

			constexpr match(const value_type &&val)
				: _value(val), _fallthrough(false), _defaultCallback([]() {}), _actions() {
				this->all();
			}
			constexpr match(const value_type &val)
				: _value(val), _fallthrough(false), _defaultCallback([]() {}), _actions() {
				this->all();
			}

			constexpr match &all() noexcept {
				this->_min = 0;
				this->_max = ~0;
				this->_jump = 0;
				this->_keepGoing = true;
				return *this;
			}
			constexpr match &first() noexcept {
				this->_min = 0;
				this->_max = 1;
				return *this;
			}
			constexpr match &last() noexcept {
				this->_min = ~0;
				this->_max = 0;
				return *this;
			}
			constexpr match &atLeast(size_t n) noexcept {
				this->_min = n;
				this->_max = ~0;
				return *this;
			}
			constexpr match &atMost(size_t n) noexcept {
				this->_min = 0;
				this->_max = n;
				return *this;
			}
			constexpr match &exactly(size_t n) noexcept {
				this->_min = n;
				this->_max = n;
				return *this;
			}
			constexpr match &every(uint8_t n) noexcept {
				this->_jump = n % 64;
				return *this;
			}


			constexpr match &ifAnyOf(const value_type &match0, const auto &...matches) noexcept {
				if (this->_newAction(this->_value == match0));
				else
					if constexpr (sizeof...(matches) > 0)
						this->ifAnyOf(matches...);

				return *this;
			}
			constexpr match &ifSatisfies(bool expression) noexcept {
				this->_newAction(expression);

				return *this;
			}

			constexpr match &Do(callback_t callback) noexcept {
				if (this->_fallthrough) this->_actions.back() = callback;

				return *this;
			}
			constexpr match &Break() noexcept {
				this->_fallthrough = false;
				return *this;
			}
			constexpr void Default(callback_t callback) noexcept {
				if (this->_fallthrough || this->_actions.size() == 0)
					this->_actions.push_back(callback);

				return this->_eval();
			}

			constexpr bool _newAction(bool predicate) noexcept {
				if (predicate || this->_fallthrough) {
					this->_fallthrough = true;
					this->_actions.push_back(this->_defaultCallback);
					this->_remaining++;
					return true;
				}

				return false;
			}
			constexpr void _updateFlags() noexcept {
				static uint8_t change = 0;
				change -= this->_remaining;

				this->_pattern = 0;
				this->_pattern |= 1ull << this->_jump + this._min;

				change = this->_remaining;
			}

			constexpr void _eval() const noexcept {
				for (const auto &callee : this->_actions) {
					callee();
				}

				return;
			}
		};
	}

	


}
