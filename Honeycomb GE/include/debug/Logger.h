#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace Honeycomb { namespace Debug {
	/// The possible types of log messages.
	enum MessageType {
		ENTRY,		// Regular Entry
		ERROR,		// Critical Error
		WARNING		// Warning
	};

	class Logger {
	public:
		/// Gets the reference to the singleton Logger instance.
		/// return : The reference to the Logger.
		static Logger& getLogger();

		/// Logs the specified message using the following format:
		/// logCount | ENTRY ~ calFunc::calLine < GameTime::elapsedTimeMS() >
		///		msg
		/// const string &calFunc : The function which requested the log; it is
		///							recommended that the macro __FUNCTION__ be 
		///							used for this.
		/// const int &calLine : The line in the script which requested the 
		///						 log; it is recommended that the macro 
		///						 __LINE__ be used for this.
		///	const string &msg : The message to be printed out.
		void logEntry(const std::string &calFunc, const int &calLine,
			const std::string &msg);

		/// Logs the specified message using the following format:
		/// logCount | ERROR ~ calFunc::calLine < GameTime::elapsedTimeMS() >
		///		msg
		/// const string &calFunc : The function which requested the log; it is
		///							recommended that the macro __FUNCTION__ be 
		///							used for this.
		/// const int &calLine : The line in the script which requested the 
		///						 log; it is recommended that the macro 
		///						 __LINE__ be used for this.
		///	const string &msg : The message to be printed out.
		void logError(const std::string &calFunc, const int &calLine,
			const std::string &msg);

		/// Logs the specified message using the following format:
		/// logCount | WARNING ~ calFunc::calLine < GameTime::elapsedTimeMS() >
		///		msg
		/// const string &calFunc : The function which requested the log; it is
		///							recommended that the macro __FUNCTION__ be 
		///							used for this.
		/// const int &calLine : The line in the script which requested the 
		///						 log; it is recommended that the macro 
		///						 __LINE__ be used for this.
		///	const string &msg : The message to be printed out.
		void logWarning(const std::string &calFunc, const int &calLine,
			const std::string &msg);
	private:
		static Logger* logger; // The singleton Logger instance

		int logCount; // Number of messages logged

					  /// Initializes a new instance of the Logger class.
		Logger();

		/// Destroys this Logger instance.
		~Logger();

		/// Logs the specified message using the following format:
		/// logCount | msgType ~ calFunc::calLine < GameTime::elapsedTimeMS() >
		///		msg
		/// const string &msgType : The type of message being logged (ENTRY,
		///							WARNING or ERROR).
		/// const string &calFunc : The function which requested the log; it is
		///							recommended that the macro __FUNCTION__ be 
		///							used for this.
		/// const int &calLine : The line in the script which requested the 
		///						 log; it is recommended that the macro 
		///						 __LINE__ be used for this.
		///	const string &msg : The message to be printed out.
		void log(const std::string &msgType, const std::string &calFunc,
			const int &calLine, const std::string &msg);
	};
} }

#endif
