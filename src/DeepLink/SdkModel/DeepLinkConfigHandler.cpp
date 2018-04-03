// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeepLinkConfigHandler.h"


namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            DeepLinkConfigHandler::DeepLinkConfigHandler(Mapscene::SdkModel::MapsceneLoader& mapsceneLoader)
            : m_mapsceneLoader(mapsceneLoader)
            {
            }
            
            void DeepLinkConfigHandler::HandleDeepLink(const AppInterface::UrlData& data)
            {
                m_mapsceneLoader.LoadMapscene(data.path, false);
            }
        }
    }
}
