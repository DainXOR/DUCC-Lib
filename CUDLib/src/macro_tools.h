#pragma once

#define DUCLIB_MACRO_TOOLS

#if !defined(DUCLIB_MACRO_TOOLS)
	constexpr auto DUCLIB_STT = 0;
	constexpr auto DUCLIB_MSG = "To activate the macro tools define the macro 'DUCLIB_MACRO_TOOLS'.";

#elif defined(DUCLIB_MACRO_TOOLS) && _DUCLIB_DEBUG_LEVEL >= 0
	constexpr auto DUCLIB_STT = 1;
	constexpr auto DUCLIB_MSG = "Macro tools initialized successfully.";
		
	#if (!defined(DUCLIB_NLOG) && !defined(DUCLIB_DISABLE_ALL))
		#if !defined(NDEBUG) || defined(DUCLIB_RELEASE_LOG)

#if _DUCLIB_DEBUG_LEVEL >= 0
			#include <iostream>

			#define DUC_NONE_LOG(x, ...)					std::cout << x
			#define DUC_NONE_PAUSE(x, ...)					std::cout << x << "\n"; std::cin.get()

			// Disable at this debug level
			#define DUC_INFO_LOG(x, ...)
			#define DUC_INFO_PAUSE(x, ...)
			#define DUC_WARN_LOG(x, ...)
			#define DUC_WARN_PAUSE(x, ...)
			#define DUC_ERROR_LOG(x, std_err, ...)
			#define DUC_ERROR_PAUSE(x, std_err, ...)


			#define DUC_NOTHING(...)
			#define DUC_MESSAGE(logType, message)	DUC_ ## logType ## _LOG(message, std::exception)
			#define DUC_ERROR_MESSAGE(std_err, message)	DUC_ERROR_LOG(message, std_err)
			#define DUC_TEST_RESULT(expression, expected, success, sreturn, error, ereturn)	[](auto leftExp, auto rightExp){ if((leftExp) == rightExp){ success; return sreturn; } else{error; return ereturn; } }(expression, expected)


			#define DUC_TEST(expression, errLevel, msg) DUC_TEST_RESULT(expression, true, DUC_NOTHING(), DUC_NOTHING(), DUC_MESSAGE(errLevel, msg), DUC_NOTHING())
			#define DUC_TEST_ERROR(expression, std_err, msg) DUC_TEST_RESULT(expression, true, DUC_NOTHING(), DUC_NOTHING(), DUC_ERROR_MESSAGE(std_err, msg), DUC_NOTHING())
			#define DUC_COMPARE(x, y, comparison)		DUC_TEST_RESULT(x comparison y, true, DUC_NOTHING(), true, DUC_NOTHING(), false)


#if _DUCLIB_DEBUG_LEVEL >= 1
			#undef DUC_INFO_LOG
			#undef DUC_INFO_PAUSE

			#define DUC_INFO_LOG(x, ...)					std::cout << "[DEBUG INFO]: " << x << "\n"
			#define DUC_INFO_PAUSE(x, ...)					std::cout << "[INFO PAUSE]:" << x << "\n"; std::cin.get()

#if _DUCLIB_DEBUG_LEVEL >= 2
			#undef DUC_WARN_LOG
			#undef DUC_WARN_PAUSE

			#define DUC_WARN_LOG(x, ...)					std::cout << "[DEBUG WARN]: " << x << "\n"
			#define DUC_WARN_PAUSE(x, ...)					std::cout << "[WARN PAUSE]:" << x << "\n"; std::cin.get()

#if _DUCLIB_DEBUG_LEVEL >= 3
			#undef DUC_ERROR_LOG
			#undef DUC_ERROR_PAUSE
			
			#define DUC_ERROR_LOG(x, std_err, ...)			std::cout << "[DEBUG ERROR]: " << x << "\n"; throw std_err(x)
			#define DUC_ERROR_PAUSE(x)						std::cout << "[ERROR PAUSE]:" << x << "\n"; std::cin.get(); throw std_err(x)

#endif // DEBUG LEVEL: ERROR
#endif // DEBUG LEVEL: WARN
#endif // DEBUG LEVEL: INFO
#endif // DEBUG LEVEL: NONE
		#elif

			#define _DUCLIB_DEBUG_LEVEL 0
	
			#define DUC_NONE_LOG(...)
			#define DMP_INFO_LOG(...)
			#define DMP_WARN_LOG(...)
			#define DMP_ERROR_LOG(...)
				
			#define DUC_NONE_PAUSE(...)
			#define DMP_INFO_PAUSE(...)
			#define DMP_WARN_PAUSE(...)
			#define DMP_ERROR_PAUSE(...)
				
			#define DUC_NOTHING(...)
			#define DUC_MESSAGE(...)
			#define DUC_TEST_RESULT(...)


			#define DUC_TEST(...)
			#define DUC_COMPARE(...)
	
		#endif // NDEBUG
	#endif // DUCLIB_LOG

	#if !defined(DUCLIB_NTESTING) && !defined(DUCLIB_DISABLE_ALL)
		#if !defined(NDEBUG) || defined(DUCLIB_RELEASE_TESTING)
			#include <iostream>

			/// \Note	When entering a template function use double parentheses to surround the call.
			///			Macro confuses template parameters comma with macro arguments separator.
			#define DUC_TEST_CONSTEXPR(function_call) noexcept(function_call)

			#define DUC_TEST_FUNCTION(function_call, expectedResult)		\
			do{															\
				std::cout << std::boolalpha;							\
				std::cout <<											\
					#function_call ": " <<								\
					function_call << " -> " << expectedResult <<		\
					" | " << (function_call == expectedResult) << "\n";	\
				std::cout << std::noboolalpha;							\
			} while (false)

			#define DUC_TEST_EQUAL(f1, f2, ...)\
			do {																\
				std::cout << std::boolalpha;									\
				std::cout														\
					<< f1(__VA_ARGS__) << " == " << f2(__VA_ARGS__) << ": "		\
					<< (f1(__VA_ARGS__) == f2(__VA_ARGS__)) << "\n";			\
				std::cout << std::noboolalpha;									\
			} while (false)		
		#else
			#define DUC_TEST_CONSTEXPR(...)
			#define DUC_TEST_FUNCTION(...)
			#define DUC_TEST_EQUAL(...)

		#endif
	#endif // DUCLIB_TESTING

	#if !defined(DUCLIB_NATT) && !defined(DUCLIB_DISABLE_ALL)
		#if defined(NDEBUG) && !defined(DUCLIB_DISABLE_ATT)
			#define DUC_RNOEXCEPT		noexcept
			#define DUC_CONST_RNOEXCEPT	const DUC_RNOEXCEPT
			#define DUC_RDEPRECATE(msg) [[deprecate(msg)]]
			#define DUC_RNORETURN		[[noreturn]]

		#else
			#define DUC_RNOEXCEPT
			#define DUC_CONST_RNOEXCEPT	const DUC_RNOEXCEPT
			#define DUC_RDEPRECATE(msg)
			#define DUC_RNORETURN
		#endif

		#if defined(DUCLIB_ENABLE_LIKELY_ATT)
			#define DUC_LIKELY [[likely]]
			#define DUC_UNLIKELY [[unlikely]]
		#endif // !NDEBUG
	#endif // DUCLIB_ATT


#else
	constexpr auto DUCLIB_STT = -1;
	constexpr auto DUCLIB_MSG = "Could not initialize correctly.";

#endif // DUCLIB_MACRO_TOOLS && !DUCLIB_MT





