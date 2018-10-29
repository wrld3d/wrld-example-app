#pragma once

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace Helpers
    {
		class WhitelistUrlHelpersNative
    	{
            std::string m_whitelistUrl;
        public:
            WhitelistUrlHelpersNative(std::string whitelistUrl);
			bool IsWhitelistedUrl(std::string & url);
        };
    }
}
