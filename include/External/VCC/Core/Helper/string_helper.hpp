#pragma once
#include <string>
#include <math.h>

using namespace std;

namespace vcc
{
	inline std::wstring str2wstr(const std::string& str)
	{
		wchar_t ws[2048];
		swprintf(ws, 2048, L"%hs", str.c_str());
		return ws;
	}

	inline std::string padLeft(const std::string str, size_t length, char c)
	{
		if (length <= str.length())
			return str;
		return std::string(length - min(length, str.length()), c) + str;
	}

	inline std::string padRight(const std::string str, size_t length, char c)
	{
		if (length <= str.length())
			return str;
		return str + std::string(length - min(length, str.length()), c);
	}

	inline bool hasPrefix(const std::string str, const std::string prefix)
	{
		return str.substr(0, prefix.length()).compare(prefix) == 0;
	}

	inline bool hasPrefix(const std::wstring str, const std::wstring prefix)
	{
		return str.substr(0, prefix.length()).compare(prefix) == 0;
	}

	inline bool hasSuffix(const std::string str, const std::string suffix)
	{
		return str.substr(str.length() - suffix.length(), str.length() - 1).compare(suffix) == 0;
	}

	inline bool hasSuffix(const std::wstring str, const std::wstring suffix)
	{
		return str.substr(str.length() - suffix.length(), str.length() - 1).compare(suffix) == 0;
	}
}
