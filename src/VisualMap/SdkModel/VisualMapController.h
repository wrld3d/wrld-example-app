// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IVisualMapController.h"
#include "VisualMap.h"

#include "Types.h"
#include "CityThemes.h"
#include "Rendering.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            class VisualMapController : public IVisualMapController, protected Eegeo::NonCopyable
            {
            public:
                VisualMapController(IVisualMapModel& visualMapModel,
                                    IVisualMapStateHistory& visualMapStateHistory,
                                    Eegeo::Resources::CityThemes::ICityThemesService& themesService,
                                    Eegeo::Resources::CityThemes::ICityThemesUpdater& themesUpdater,
                                    Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService);
                
                ~VisualMapController();
                
            private:
                IVisualMapModel& m_visualMapModel;
                IVisualMapStateHistory& m_visualMapStateHistory;
                
                Eegeo::Resources::CityThemes::ICityThemesService& m_themesService;
                Eegeo::Resources::CityThemes::ICityThemesUpdater& m_themesUpdater;
                Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
                
                Eegeo::Helpers::TCallback2<VisualMapController, const VisualMapState&, const bool&> m_onVisualMapModelChanged;
                void OnVisualMapModelChanged(const VisualMapState& previousState, const bool& storePreviousState);
            };
        }
    }
}