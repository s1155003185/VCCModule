#include "log_service.hpp"

#include <iostream>

#include "datetime_helper.hpp"
#include "file_helper.hpp"

namespace vcc
{
	wstring LogService::_logMessage(LogProperty &logProperty, LogType logType, wstring id, wstring userid, wstring message)
	{
		wstring logMessage;
		switch (logType)
		{
		case LogType::Error:
			logMessage = L"[ERRO]";
			break;
		case LogType::Warning:
			logMessage = L"[WARN]";
			break;
		case LogType::Info:
			logMessage = L"[INFO]";
			break;
		default:
			logMessage = L"[INFO]";
			break;
		}

		logMessage += L" " + GetCurrentDatetimeString();
		if (!id.empty())
			logMessage += L" [" + id + L"]";
		if (!userid.empty())
			logMessage += L" [" + userid + L"] ";
		logMessage += L" " + message;
		if (logProperty.GetIsConsoleLog())
			std::wcout << logMessage << endl;

		if (!logProperty.GetFilePath().empty()) {
			AppendFileSingleLline(logProperty.GetFilePath(), logMessage, true);
		}
		return logMessage;
	}

	wstring LogService::LogInfo(wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogInfo(defaultProperty, message);
	}

	wstring LogService::LogInfo(wstring id, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogInfo(defaultProperty, id, message);
	}

	wstring LogService::LogInfo(wstring id, wstring userid, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogInfo(defaultProperty, id, userid, message);
	}

	wstring LogService::LogInfo(LogProperty &logProperty, wstring message)
	{
		return LogService::LogInfo(logProperty, L"", L"", message);
	}

	wstring LogService::LogInfo(LogProperty &logProperty, wstring id, wstring message)
	{
		return LogService::LogInfo(logProperty, id, L"", message);
	}

	wstring LogService::LogInfo(LogProperty &logProperty, wstring id, wstring userid, wstring message)
	{
		return LogService::_logMessage(logProperty, LogType::Info, id, userid, message);
	}

	wstring LogService::LogWarning(wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogWarning(defaultProperty, message);
	}

	wstring LogService::LogWarning(wstring id, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogWarning(defaultProperty, id, message);
	}

	wstring LogService::LogWarning(wstring id, wstring userid, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogWarning(defaultProperty, id, userid, message);
	}

	wstring LogService::LogWarning(LogProperty &logProperty, wstring message)
	{
		return LogService::LogWarning(logProperty, L"", message);
	}

	wstring LogService::LogWarning(LogProperty &logProperty, wstring id, wstring message)
	{
		return LogService::LogWarning(logProperty, id, L"", message);
	}

	wstring LogService::LogWarning(LogProperty &logProperty, wstring id, wstring userid, wstring message)
	{
		return LogService::_logMessage(logProperty, LogType::Warning, id, userid, message);
	}

	wstring LogService::LogError(wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogError(defaultProperty, message);
	}

	wstring LogService::LogError(wstring id, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogError(defaultProperty, id, message);
	}

	wstring LogService::LogError(wstring id, wstring userid, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogError(defaultProperty, id, userid, message);
	}

	wstring LogService::LogError(LogProperty &logProperty, wstring message)
	{
		return LogService::LogError(logProperty, L"", message);
	}

	wstring LogService::LogError(LogProperty &logProperty, wstring id, wstring message)
	{
		return LogService::LogError(logProperty, id, L"", message);
	}

	wstring LogService::LogError(LogProperty &logProperty, wstring id, wstring userid, wstring message)
	{
		return LogService::_logMessage(logProperty, LogType::Error, id, userid, message);
	}

	wstring LogService::LogCommand(wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogCommand(defaultProperty, message);
	}

	wstring LogService::LogCommand(wstring id, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogCommand(defaultProperty, id, message);
	}

	wstring LogService::LogCommand(wstring id, wstring userid, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogCommand(defaultProperty, id, userid, message);
	}

	wstring LogService::LogCommand(LogProperty &logProperty, wstring message)
	{
		return LogService::LogCommand(logProperty, L"", L"", message);
	}

	wstring LogService::LogCommand(LogProperty &logProperty, wstring id, wstring message)
	{
		return LogService::LogCommand(logProperty, id, L"", message);
	}

	wstring LogService::LogCommand(LogProperty &logProperty, wstring id, wstring userid, wstring message)
	{
		if (!logProperty.GetIsLogCommand())
			return L"";
		return LogService::_logMessage(logProperty, LogType::Info, id, userid, message);
	}

	wstring LogService::LogCommandResult(wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogCommandResult(defaultProperty, message);
	}

	wstring LogService::LogCommandResult(wstring id, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogCommandResult(defaultProperty, id, message);
	}

	wstring LogService::LogCommandResult(wstring id, wstring userid, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogCommandResult(defaultProperty, id, userid, message);
	}

	wstring LogService::LogCommandResult(LogProperty &logProperty, wstring message)
	{
		return LogService::LogCommandResult(logProperty, L"", L"", message);
	}

	wstring LogService::LogCommandResult(LogProperty &logProperty, wstring id, wstring message)
	{
		return LogService::LogCommandResult(logProperty, id, L"", message);
	}

	wstring LogService::LogCommandResult(LogProperty &logProperty, wstring id, wstring userid, wstring message)
	{
		if (!logProperty.GetIsLogCommandResult())
			return L"";
		return LogService::_logMessage(logProperty, LogType::Info, id, userid, message);
	}

	wstring LogService::LogProcess(wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogProcess(defaultProperty, message);
	}

	wstring LogService::LogProcess(wstring id, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogProcess(defaultProperty, id, message);
	}

	wstring LogService::LogProcess(wstring id, wstring userid, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogProcess(defaultProperty, id, userid, message);
	}

	wstring LogService::LogProcess(LogProperty &logProperty, wstring message)
	{
		return LogService::LogProcess(logProperty, L"", L"", message);
	}

	wstring LogService::LogProcess(LogProperty &logProperty, wstring id, wstring message)
	{
		return LogService::LogProcess(logProperty, id, L"", message);
	}

	wstring LogService::LogProcess(LogProperty &logProperty, wstring id, wstring userid, wstring message)
	{
		if (!logProperty.GetIsLogProcess())
			return L"";
		return LogService::_logMessage(logProperty, LogType::Info, id, userid, message);
	}

	wstring LogService::LogProcessResult(wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogProcessResult(defaultProperty, message);
	}

	wstring LogService::LogProcessResult(wstring id, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogProcessResult(defaultProperty, id, message);
	}

	wstring LogService::LogProcessResult(wstring id, wstring userid, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogProcessResult(defaultProperty, id, userid, message);
	}

	wstring LogService::LogProcessResult(LogProperty &logProperty, wstring message)
	{
		return LogService::LogProcessResult(logProperty, L"", L"", message);
	}

	wstring LogService::LogProcessResult(LogProperty &logProperty, wstring id, wstring message)
	{
		return LogService::LogProcessResult(logProperty, id, L"", message);
	}

	wstring LogService::LogProcessResult(LogProperty &logProperty, wstring id, wstring userid, wstring message)
	{
		if (!logProperty.GetIsLogProcessResult())
			return L"";
		return LogService::_logMessage(logProperty, LogType::Info, id, userid, message);
	}

	wstring LogService::LogSQL(wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogSQL(defaultProperty, message);
	}

	wstring LogService::LogSQL(wstring id, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogSQL(defaultProperty, id, message);
	}

	wstring LogService::LogSQL(wstring id, wstring userid, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogSQL(defaultProperty, id, userid, message);
	}

	wstring LogService::LogSQL(LogProperty &logProperty, wstring message)
	{
		return LogService::LogSQL(logProperty, L"", L"", message);
	}

	wstring LogService::LogSQL(LogProperty &logProperty, wstring id, wstring message)
	{
		return LogService::LogSQL(logProperty, id, L"", message);
	}

	wstring LogService::LogSQL(LogProperty &logProperty, wstring id, wstring userid, wstring message)
	{
		if (!logProperty.GetIsLogSQL())
			return L"";
		return LogService::_logMessage(logProperty, LogType::Info, id, userid, message);
	}

	wstring LogService::LogSQLResult(wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogSQLResult(defaultProperty, message);
	}

	wstring LogService::LogSQLResult(wstring id, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogSQLResult(defaultProperty, id, message);
	}

	wstring LogService::LogSQLResult(wstring id, wstring userid, wstring message)
	{
		LogProperty defaultProperty;
		return LogService::LogSQLResult(defaultProperty, id, userid, message);
	}

	wstring LogService::LogSQLResult(LogProperty &logProperty, wstring message)
	{
		return LogService::LogSQLResult(logProperty, L"", L"", message);
	}

	wstring LogService::LogSQLResult(LogProperty &logProperty, wstring id, wstring message)
	{
		return LogService::LogSQLResult(logProperty, id, L"", message);
	}

	wstring LogService::LogSQLResult(LogProperty &logProperty, wstring id, wstring userid, wstring message)
	{
		if (!logProperty.GetIsLogSQLResult())
			return L"";
		return LogService::_logMessage(logProperty, LogType::Info, id, userid, message);
	}
}
