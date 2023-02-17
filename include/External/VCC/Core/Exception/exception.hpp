#pragma once
#include <exception>
#include <string>

#include "common_helper.hpp"
#include "class_macro.hpp"
#include "exception_type.hpp"

using namespace std;

namespace vcc
{
	struct Exception : public std::exception
	{
		GET(ExceptionType, ExceptionType, ExceptionType::NA)
		GET(std::wstring, ErrorMessage, L"")

	public:
		Exception() : Exception(ExceptionType::NA) {}
		Exception(ExceptionType ExceptionType) : Exception(ExceptionType, L"") {}
		Exception(ExceptionType ExceptionType, std::wstring errorMessage)
		{
			this->_ExceptionType = ExceptionType;
			this->_ErrorMessage = errorMessage;
		}

		const char* what() const throw ()
		{
			//const char* errorMsg = wstr2str(this->_ErrorMessage).c_str();
			//return errorMsg;
			return nullptr;
		}
	};

	//struct NoError : public Exception
	//{
	//	NoError() : Exception(ExceptionType::NA, L"") {}
	//};

	//EXCEPTION(FileNotFoundException, FILE_NOT_FOUND, L"FILE_NOT_FOUND")
}