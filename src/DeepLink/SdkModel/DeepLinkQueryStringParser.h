// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <string>
#include "AppInterface.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class DeepLinkQueryStringParser
            {
            public:
                DeepLinkQueryStringParser();
                void ParseData(const std::string& query);
                bool HasIndoorId();
                bool HasMapScene();
                bool HasValidQueryString();
                AppInterface::UrlData GetSearchData(const AppInterface::UrlData& data);
                AppInterface::UrlData GetMapsceneData(const AppInterface::UrlData& data);
            private:
                bool m_hasValidQueryString;
                bool m_hasIndoorId;
                bool m_hasMapScene;
                std::string m_indoorId;
                std::string m_mapsceneString;
            };
        }
    }
}

