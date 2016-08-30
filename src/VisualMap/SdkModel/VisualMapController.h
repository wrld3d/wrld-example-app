// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IVisualMapController.h"
#include "VisualMap.h"

#include "Types.h"
#include "CityThemes.h"
#include "Rendering.h"
#include "ICallback.h"

#include <memory>

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            class VisualMapController : public IVisualMapController, protected Eegeo::NonCopyable
            {
            public:
                VisualMapController(const std::shared_ptr<IVisualMapModel>& visualMapModel,
                                    const std::shared_ptr<IVisualMapStateHistory>& visualMapStateHistory,
                                    const std::shared_ptr<Eegeo::Resources::CityThemes::ICityThemesService>& themesService,
                                    const std::shared_ptr<Eegeo::Resources::CityThemes::ICityThemesUpdater>& themesUpdater,
                                    const std::shared_ptr<Eegeo::Rendering::EnvironmentFlatteningService>& environmentFlatteningService);
                
                ~VisualMapController();
                
            private:
                std::shared_ptr<IVisualMapModel> m_visualMapModel;
                std::shared_ptr<IVisualMapStateHistory> m_visualMapStateHistory;
                
                std::shared_ptr<Eegeo::Resources::CityThemes::ICityThemesService> m_themesService;
                std::shared_ptr<Eegeo::Resources::CityThemes::ICityThemesUpdater> m_themesUpdater;
                std::shared_ptr<Eegeo::Rendering::EnvironmentFlatteningService> m_environmentFlatteningService;
                
                Eegeo::Helpers::TCallback2<VisualMapController, const VisualMapState&, const bool&> m_onVisualMapModelChanged;
                void OnVisualMapModelChanged(const VisualMapState& previousState, const bool& storePreviousState);
            };
        }
    }
}