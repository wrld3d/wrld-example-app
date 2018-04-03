// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <string>
#include "AppInterface.h"
#include "QueryData.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class DeepLinkQueryStringParser
            {
            public:
                QueryData ParseData(const AppInterface::UrlData& data) const;
            private:
            };
            
        }
    }
}

