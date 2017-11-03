//Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once
#include "AppInterface.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class IDeepLinkHandler
            {
            public:
                virtual void HandleDeepLink(const AppInterface::UrlData& data) =0;
                virtual ~IDeepLinkHandler() {};
            };
        }
    }
}
