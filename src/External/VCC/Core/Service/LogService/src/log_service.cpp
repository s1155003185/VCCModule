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
		logMessage += message;
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
}
