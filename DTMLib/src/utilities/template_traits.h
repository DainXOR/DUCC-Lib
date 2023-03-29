#pragma once

#include <array>

namespace duc {
	namespace math_utils {
		namespace template_traits {
			namespace {
				template<bool test, auto val>
				struct false_or_value_s {
				};

				template<auto val>
				struct false_or_value_s<false, val> {
					static constexpr bool value = false;
				};

				template<auto val>
				struct false_or_value_s<true, val> {
					static constexpr auto value = val;
				};
			}

			template<bool test, auto value>
			inline constexpr auto false_or_value = false_or_value_s<test, value>::value;

			template<bool test, auto value>
			inline constexpr auto true_or_value = false_or_value_s<!test, value>::value;

		}

		namespace helper {

			template <typename size_type, std::size_t Size>
			[[nodiscard]] constexpr std::array<size_type, Size> getMultipliers(const std::array<size_type, Size>& values) noexcept {

				std::array<size_type, Size> multipliersArray{};

				multipliersArray[Size - 1] = 1;
				((multipliersArray[Size - i - 2] = multipliersArray[Size - i - 1] * values[Size - i - 1]), ...);

				return multipliersArray;
			}

		}
	}

}