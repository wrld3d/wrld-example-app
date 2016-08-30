// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MapMode.h"
#include "VisualMap.h"

#include <string>
#include <ICallback.h>

namespace ExampleApp
{
    namespace MapMode
    {
        namespace SdkModel
        {
            class MapModeController
            {
            public:
                MapModeController(const std::shared_ptr<IMapModeModel>& mapModeModel,
                                  const std::shared_ptr<VisualMap::SdkModel::IVisualMapService>& visualMapService);

                ~MapModeController();

            private:
                const std::shared_ptr<IMapModeModel> m_mapModeModel;
                const std::shared_ptr<VisualMap::SdkModel::IVisualMapService> m_visualMapService;

                void OnMapModeChanged();
                Eegeo::Helpers::TCallback0<MapModeController> m_onMapModeChangedCallback;
            };
        }
    }
}