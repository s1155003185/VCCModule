#pragma once
#include <string>
#include <math.h>

using namespace std;

namespace vcc
{
	inline wstring str2wstr(const string& str)
	{
		wchar_t ws[2048];
		swprintf(ws, 2048, L"%hs", str.c_str());
		return ws;
	}

	inline string PadLeft(const string str, size_t length, char c)
	{
		if (length <= str.length())
			return str;
		return std::string(length - min(length, str.length()), c) + str;
	}

	inline string PadRight(const string str, size_t length, char c)
	{
		if (length <= str.length())
			return str;
		return str + std::string(length - min(length, str.length()), c);
	}

	inline bool HasPrefix(const string str, const string prefix)
	{
		return str.substr(0, prefix.length()).compare(prefix) == 0;
	}

	inline bool HasPrefix(const wstring str, const wstring prefix)
	{
		return str.substr(0, prefix.length()).compare(prefix) == 0;
	}

	inline bool HasSuffix(const string str, const string suffix)
	{
		return str.substr(str.length() - suffix.length(), str.length() - 1).compare(suffix) == 0;
	}

	inline bool HasSuffix(const wstring str, const wstring suffix)
	{
		return str.substr(str.length() - suffix.length(), str.length() - 1).compare(suffix) == 0;
	}
}
