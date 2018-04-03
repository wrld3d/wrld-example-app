// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IDeepLinkHandler.h"
#include "MapsceneLoader.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class DeepLinkConfigHandler: public IDeepLinkHandler, private Eegeo::NonCopyable
            {
            public:
                DeepLinkConfigHandler(Mapscene::SdkModel::MapsceneLoader& mapsceneLoader);
                void HandleDeepLink(const AppInterface::UrlData& data);
            private:
                Mapscene::SdkModel::MapsceneLoader& m_mapsceneLoader;
            };
        }
    }
}
