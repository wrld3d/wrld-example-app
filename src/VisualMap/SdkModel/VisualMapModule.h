// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IVisualMapModule.h"
#include "VisualMap.h"

#include "Types.h"
#include "Rendering.h"
#include "CityThemes.h"


namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            class VisualMapModule : public IVisualMapModule, protected Eegeo::NonCopyable
            {
            public:
                VisualMapModule(Eegeo::Resources::CityThemes::ICityThemesService& themesService,
                                Eegeo::Resources::CityThemes::ICityThemesUpdater& themesUpdater,
                                Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService);
                
                ~VisualMapModule();
                
                IVisualMapService& GetVisualMapService() const;
                
            private:
                IVisualMapModel* m_pVisualMapModel;
                IVisualMapStateHistory* m_pVisualMapStateHistory;
                IVisualMapController* m_pVisualMapController;
                IVisualMapService* m_pVisualMapService;
            };
        }
    }
}