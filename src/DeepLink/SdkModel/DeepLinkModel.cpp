// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeepLinkModel.h"
#include <unordered_map>
#include <utility>

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            DeepLinkModel::~DeepLinkModel()
            {
                ClearRoutes();
            }

            void DeepLinkModel::AddRoute(const std::string& name, IDeepLinkHandler* route)
            {
                m_routes.insert({name, route});
            }

            void DeepLinkModel::RemoveRoute(const std::string& name)
            {
                m_routes.erase(name);
            }

            void DeepLinkModel::ClearRoutes()
            {
                for(std::unordered_map<std::string, IDeepLinkHandler*>::iterator it = m_routes.begin(); it != m_routes.end(); ++it)
                {
                    Eegeo_DELETE(it->second);
                }
                m_routes.clear();
            }

            IDeepLinkHandler* DeepLinkModel::Get(const std::string& key)
            {
                std::unordered_map<std::string, IDeepLinkHandler*>::iterator it = m_routes.find(key);
                if(it != m_routes.end())
                {
                    return it->second;
                }
                else
                {
                    return NULL;
                }
            }
        }
    }
}
