// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMapModeModel.h"
#include "Rendering.h"
#include "IWeatherController.h"
#include "CallbackCollection.h"

#include <string>

namespace ExampleApp
{
    namespace MapMode
    {
        namespace SdkModel
        {
            class MapModeModel : public IMapModeModel
            {
            public:
                MapModeModel();
                ~MapModeModel();

                bool IsInMapMode() const;
                void SetInMapMode(bool inMapMode);

                void AddMapModeChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveMapModeChangedCallback(Eegeo::Helpers::ICallback0& callback);

            private:
                bool m_inMapMode;

                Eegeo::Helpers::CallbackCollection0 m_mapModeChangedCallbacks;
            };
        }
    }
}



