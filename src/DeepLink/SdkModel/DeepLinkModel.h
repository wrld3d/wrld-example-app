// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IDeepLinkHandler.h"
#include <unordered_map>
#include <string>

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class DeepLinkModel: private Eegeo::NonCopyable
            {
            public:
                DeepLinkModel() {};
                ~DeepLinkModel();
                void AddRoute(const std::string& name, IDeepLinkHandler* route);
                void RemoveRoute(const std::string& name);
                void ClearRoutes();
                IDeepLinkHandler* Get(const std::string& key);
            private:
                std::unordered_map<std::string, IDeepLinkHandler*> m_routes;
            };
        }
    }
}
