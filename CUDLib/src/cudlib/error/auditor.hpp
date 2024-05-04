#pragma once

#include <string>
#include <vector>

namespace duc {
	struct simple_sender {
		std::string name;

		std::string formatName() const noexcept { return name; }
	};

	template<class msg_t = std::string, class sender_t = simple_sender >
	class auditor {
		class builder;
	public:
		
		enum severity {
			VERBOSE = 0,
			DEBUG = 1,
			INFO = 2,
			USER_LOW = 2,
			WARNING = 3,
			USER_MEDIUM = 4,
			ERROR = 5,
			USER_HIGH = 6,
			FATAL = 7
		};

		static builder buildMessage();

		static bool log(msg_t, sender_t, severity);
		static bool msg(msg_t, sender_t);
		static bool info(msg_t, sender_t);
		static bool debug(msg_t, sender_t);
		static bool warning(msg_t, sender_t);
		static bool error(msg_t, sender_t);
		static bool fatal(msg_t, sender_t);

		static bool user_l(msg_t, sender_t);
		static bool user_m(msg_t, sender_t);
		static bool user_h(msg_t, sender_t);

		static void setLogLevel(severity);
		static severity getLogLevel();

		static void setTraceLevel(severity);
		static severity getTraceLevel();

		static void setRecordTrace(bool);

	private:
		static bool sendMessage(msg_t, severity);
		static bool addTrace(msg_t, severity);
		static bool printTrace();

		static msg_t getTimestamp();
		static msg_t getSenderName(sender_t);
		static msg_t getSeverityName(severity);
		static msg_t getSeverityColor(severity);
		static msg_t getTimeStampColor();
		static msg_t getMessageColor();
		static msg_t resetColor();

		static msg_t formatMessage(msg_t, sender_t, severity);

	private:
		static severity logLevel;
		static bool recordTrace;
		static severity traceLevel;
		static std::vector<msg_t> trace;

		static const std::vector<std::string> senderNames;
		static const std::vector<std::string> severityNames;
		static const std::vector<std::string> severityColors;
		static const std::string colorReset;
		static const std::string timeStampColor;
		static const std::string messageColor;

		// make a static constexpr array of pointers to the functions
		static constexpr bool (*severityFunctions[])(msg_t, sender_t) = {
			debug, error, warning, info, fatal
		};

	private:
		class builder {
			msg_t message = "";
			sender_t who = sender_t{ "SERVER", 0 };
			severity level = severity::INFO;
		public:
			builder add(msg_t);
			builder setSender(sender_t);
			builder setSeverity(severity);
			bool log();
			msg_t getMessage();
			msg_t getFormatedMessage();
		};

	};
}