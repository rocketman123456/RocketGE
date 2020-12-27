#include "GEUtils/PlatformUtils.h"

namespace Rocket
{
    std::optional<std::string> FileDialogs::OpenFile(const char* filter)
	{
        std::fstream file(filter, std::ios::in);

		if (!file.is_open()) 
		{
			return std::nullopt;
		}
		else
		{
			file.close();
			return filter;
		}
	}

    std::optional<std::string> FileDialogs::SaveFile(const char* filter)
	{
        std::fstream file(filter, std::ios::out);

		if (!file.is_open()) 
		{
			return std::nullopt;
		}
		else
		{
			file.close();
			return filter;
		}
	}
}