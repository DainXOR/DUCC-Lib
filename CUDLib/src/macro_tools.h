#pragma once


//#define DUCLIB_MT
//#define DUCLIB_LOG
//#include <iostream>

#if !defined(DUCLIB_MT) && defined(DUCLIB_MACRO_TOOLS)
	#define DUCLIB_STT 1
	#define DUCLIB_MSG "Macro tools initialized successfully"
		
	#ifdef DUCLIB_LOG
		#if !defined(NDEBUG) && defined(_IOSTREAM_)
			#define _DUCLIB_DEBUG 1
				
			#define DUC_INFO_LOG(x)				std::cout << "[DEBUG INFO]: " << x << "\n";
			#define DUC_WARN_LOG(x)				std::cout << "[WARN INFO]: " << x << "\n";
			#define DUC_ERROR_LOG(std_err, x)		std::cout << "[ERROR INFO]: " << x << "\n"; throw std_err(x)
				
			#define DUC_INFO_PAUSE(x)				std::cout << "[DEBUG PAUSE]" << x << "\n"; std::cin.get()
			#define DUC_WARN_PAUSE(x)				std::cout << "[WARN PAUSE]" << x << "\n"; std::cin.get()
			#define DUC_ERROR_PAUSE(x)				std::cout << "[ERROR PAUSE]" << x << "\n"; std::cin.get(); throw std_err(x)
				
			#define DUC_TEST(expression, expected) _DUC_TEST_RESULT
			#define DUC_COMPARE(x, y)
			#define DUC_TEST_RESULT(expression, expected, succeed, error)
				
		
		#else
			#if !defined(NDEBUG) && !defined(_IOSTREAM_)
				#define DUCLIB_MT -1
				#define DUCLIB_MSG "The <iostream> library is required but not included."
			#endif

			#define DUCLIB_DEBUG 0
	
			#define DMP_INFO_LOG(x)
			#define DMP_WARN_LOG(x)
			#define DMP_ERROR_LOG(std_err, x) throw std_err(x)
				
			#define DMP_INFO_PAUSE(x)
			#define DMP_WARN_PAUSE(x)
			#define DMP_ERROR_PAUSE(x)
				
			#define DMP_COMPARE(x, y)
			#define DMP_TEST(expression, expected, succeed, error)
			#define DMP_TEST_RESULT(expression, expected)
	
		#endif // NDEBUG
	#endif // DUCLIB_LOG
	#ifdef DUCLIB_TESTING
		/// \Note	When entering a template function use double parentheses to surround the call.
		///			Macro confuses template parameters comma with macro arguments separator.
		#define IS_CONSTEXPR(function_call) noexcept(function_call)
		
	#endif // DUCLIB_TESTING

	#ifdef DUCLIB_ATT
		#define
	#endif // DUCLIB_ATT


#elif defined(DUCLIB_MT)
	#define DUCLIB_MT -1
	#define DUCLIB_MSG "Could not initialize correctly."

#endif // DUCLIB_MACRO_TOOLS && !DUCLIB_MT





