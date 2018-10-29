//
//  URLHelpers.cpp
//  ProjectSwallowApp
//
//  Created by Harry French on 16/07/2018.
//

#include "WhitelistUrlHelpersNative.h"

namespace ExampleApp
{
    namespace Helpers
    {
        WhitelistUrlHelpersNative::WhitelistUrlHelpersNative(std::string whitelistURL)
        :m_whitelistUrl(whitelistURL)
        {
            
        }
        
        bool WhitelistUrlHelpersNative::IsWhitelistedUrl(std::string &url)
        {
            auto domainEndPosition  = url.find(".com", 0) + 4;
            auto domainBeginPosition  = url.find("://", 0) + 3;

            if (domainEndPosition == std::string::npos)
            {
                return false; // definitely not a valid url
            }

            std::string domain = std::string(url.begin() + domainBeginPosition, url.begin() +  domainEndPosition);

			if(domain == m_whitelistUrl)
			{
				return true;
			}

            return false;
        }
    }
}
