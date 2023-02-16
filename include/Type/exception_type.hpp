#pragma once

enum class ExceptionType
{
    NA = 0,
    // vccobj - begin
	// Directory
	DIRECTORY_NOT_FOUND,
	DIRECTORY_CANNOT_CREATE,
    // File
	FILE_NOT_FOUND,
	FILE_CANNOT_OPEN,
    // vccobj - end
};