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

		// General
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
		
		// Command
		static wstring LogCommand(wstring message);
		static wstring LogCommand(wstring id, wstring message);
		static wstring LogCommand(wstring id, wstring userid, wstring message);
		static wstring LogCommand(LogProperty &logProperty, wstring message);
		static wstring LogCommand(LogProperty &logProperty, wstring id, wstring message);
		static wstring LogCommand(LogProperty &logProperty, wstring id, wstring userid, wstring message);

		static wstring LogCommandResult(wstring message);
		static wstring LogCommandResult(wstring id, wstring message);
		static wstring LogCommandResult(wstring id, wstring userid, wstring message);
		static wstring LogCommandResult(LogProperty &logProperty, wstring message);
		static wstring LogCommandResult(LogProperty &logProperty, wstring id, wstring message);
		static wstring LogCommandResult(LogProperty &logProperty, wstring id, wstring userid, wstring message);
		
		// SQL
		static wstring LogSQL(wstring message);
		static wstring LogSQL(wstring id, wstring message);
		static wstring LogSQL(wstring id, wstring userid, wstring message);
		static wstring LogSQL(LogProperty &logProperty, wstring message);
		static wstring LogSQL(LogProperty &logProperty, wstring id, wstring message);
		static wstring LogSQL(LogProperty &logProperty, wstring id, wstring userid, wstring message);
		
		static wstring LogSQLResult(wstring message);
		static wstring LogSQLResult(wstring id, wstring message);
		static wstring LogSQLResult(wstring id, wstring userid, wstring message);
		static wstring LogSQLResult(LogProperty &logProperty, wstring message);
		static wstring LogSQLResult(LogProperty &logProperty, wstring id, wstring message);
		static wstring LogSQLResult(LogProperty &logProperty, wstring id, wstring userid, wstring message);
	};
}
