#pragma once
#include <chrono>
#include <limits>
#include <random>
#include <tuple>
#include <vector>

#define ENABLE_EXPERIMENTAL_MACROS
#include "experimental.h"


namespace duc::benchmark {
	std::random_device rd;
	std::mt19937 gen(rd());

	template<typename... Args>
	std::vector<std::tuple<Args...>> generateRandomNumbers(int n, std::array<Args, 2>... limits) {
		std::vector<std::tuple<Args...>> inputs(n);

		auto generate_random_arg = [&](auto min, auto max) {
			using min_type = decltype(min);
			using max_type = decltype(max);

			if (min == max) { // Check if limits are equal
				std::uniform_int_distribution<> dist(
					std::numeric_limits<min_type>::min(),
					std::numeric_limits<max_type>::max());

				return static_cast<decltype(min)>(dist(gen));
			}
			else {
				std::uniform_int_distribution<> dist(min, max);
				return static_cast<decltype(min)>(dist(gen));
			}
		};

		for (int i = 0; i < n; ++i) {
			inputs[i] = std::make_tuple(generate_random_arg(limits[0], limits[1])...);
		}

		return inputs;
	}

	/*
	template<typename... Args>
	uint64_t benchmark(auto function, std::vector<std::tuple<Args...>> inputs = {}) {
		constexpr uint32_t testIterations = 10000000;
		constexpr size_t argsNumber = sizeof...(Args);

		if (inputs.empty()) {
			generateRandomNumbers(testIterations, USE_N({}, argsNumber));
		}
	}
	*/

}
/*
#define BENCHMARK2(func, inputs)                                                   \
    do {                                                                           \
        auto start = std::chrono::high_resolution_clock::now();                    \
        for (int i = 0; i < BM_ITER; i++) {                                        \
            std::apply([](auto&&... args) { func(args...); }, inputs[i]);          \
        }                                                                          \
        auto end = std::chrono::high_resolution_clock::now();                      \
        std::cout << #func << " elapsed time: "                                    \
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() \
                  << " nanoseconds" << std::endl;                                 \
    } while (false)


*/