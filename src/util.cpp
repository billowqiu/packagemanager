#include "util.h"
#include <string.h>

std::string translateError(int aError)
{
#ifdef _WIN32
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		aError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL
		);

	std::string tmp = reinterpret_cast<const char*>(lpMsgBuf);
	LocalFree( lpMsgBuf );
#else
	std::string tmp = strerror(aError);
#endif
	std::string::size_type i = 0;

	while( (i = tmp.find_first_of("\r\n", i)) != std::string::npos)
	{
		tmp.erase(i, 1);
	}
	return tmp;
}
