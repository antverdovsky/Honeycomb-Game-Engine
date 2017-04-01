#include "../../include/debug/Logger.h"

#include <iostream>
#include <iomanip>

#include "../../include/base/GameTime.h"

using Honeycomb::Base::GameTime;

namespace Honeycomb::Debug {
	Logger* Logger::logger = nullptr;

	Logger& Logger::getLogger() {
		if (logger == nullptr) logger = new Logger();

		return *logger;
	}

	void Logger::logEntry(const std::string &calFunc,
			const int &calLine, const std::string &msg) {
		this->log("ENTRY", calFunc, calLine, msg);
	}

	void Logger::logError(const std::string &calFunc,
			const int &calLine, const std::string &msg) {
		this->log("ERROR", calFunc, calLine, msg);
	}

	void Logger::logWarning(const std::string &calFunc,
			const int &calLine, const std::string &msg) {
		this->log("WARNING", calFunc, calLine, msg);
	}

	Logger::Logger() {
		this->logCount = 0;
	}

	Logger::~Logger() {

	}

	void Logger::log(const std::string &msgType, const std::string &calFunc,
			const int &calLine, const std::string &msg) {
#if _DEBUG
		// Print out the message
		std::cout << std::setfill('0') << std::setw(7) << this->logCount <<
			" | " << msgType << " ~ " << calFunc << "::" << calLine << " < " <<
			GameTime::getGameTime()->getElapsedTimeMS() << " > "
			<< "\n\t" << msg << std::endl;

		this->logCount++; // Another message has been logged
#endif
	}
}