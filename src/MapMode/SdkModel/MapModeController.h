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
                MapModeController(IMapModeModel& mapModeModel,
                                  VisualMap::SdkModel::IVisualMapService& visualMapService);

                ~MapModeController();

            private:
                IMapModeModel& m_mapModeModel;
                VisualMap::SdkModel::IVisualMapService& m_visualMapService;

                void OnMapModeChanged();
                Eegeo::Helpers::TCallback0<MapModeController> m_onMapModeChangedCallback;
            };
        }
    }
}