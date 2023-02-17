#pragma once
#include "base_service.hpp"

#include <string>

#include "log_property.hpp"
#include "log_type.hpp"

using namespace std;

namespace vcc
{
	class LogService : public BaseService
	{
	private:
		static wstring _logMessage(LogProperty &logProperty, LogType logType, wstring id, wstring userid, wstring message);

	public:
		LogService() : BaseService() {}
		~LogService() {}

		static wstring LogInfo(wstring message);
		static wstring LogInfo(wstring id, wstring message);
		static wstring LogInfo(wstring id, wstring userid, wstring message);
		static wstring LogInfo(LogProperty &logProperty, wstring message);
		static wstring LogInfo(LogProperty &logProperty, wstring id, wstring message);
		static wstring LogInfo(LogProperty &logProperty, wstring id, wstring userid, wstring message);

		static wstring LogWarning(wstring message);
		static wstring LogWarning(wstring id, wstring message);
		static wstring LogWarning(wstring id, wstring userid, wstring message);
		static wstring LogWarning(LogProperty &logProperty, wstring message);
		static wstring LogWarning(LogProperty &logProperty, wstring id, wstring message);
		static wstring LogWarning(LogProperty &logProperty, wstring id, wstring userid, wstring message);

		static wstring LogError(wstring message);
		static wstring LogError(wstring id, wstring message);
		static wstring LogError(wstring id, wstring userid, wstring message);
		static wstring LogError(LogProperty &logProperty, wstring message);
		static wstring LogError(LogProperty &logProperty, wstring id, wstring message);
		static wstring LogError(LogProperty &logProperty, wstring id, wstring userid, wstring message);
	};
}
