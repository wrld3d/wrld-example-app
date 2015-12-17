// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "VisualMapModule.h"
#include "VisualMapModel.h"
#include "VisualMapStateHistory.h"
#include "VisualMapController.h"
#include "VisualMapService.h"
#include "VisualMapState.h"

#include "EnvironmentFlatteningService.h"
#include "ICityThemesService.h"
#include "CityThemeData.h"

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            VisualMapModule::VisualMapModule(Eegeo::Resources::CityThemes::ICityThemesService& themesService,
                                             Eegeo::Resources::CityThemes::ICityThemesUpdater& themesUpdater,
                                             Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService)
            {
                VisualMapState initalState("Summer", "DayDefault", false);
                m_pVisualMapModel = Eegeo_NEW(VisualMapModel)(initalState);
                m_pVisualMapStateHistory = Eegeo_NEW(VisualMapStateHistory)();
                m_pVisualMapController = Eegeo_NEW(VisualMapController)(*m_pVisualMapModel,
                                                                        *m_pVisualMapStateHistory,
                                                                        themesService,
                                                                        themesUpdater,
                                                                        environmentFlatteningService);
                
                m_pVisualMapService = Eegeo_NEW(VisualMapService)(*m_pVisualMapModel, *m_pVisualMapStateHistory);
            }
            
            VisualMapModule::~VisualMapModule()
            {
                Eegeo_DELETE m_pVisualMapService;
                Eegeo_DELETE m_pVisualMapController;
                Eegeo_DELETE m_pVisualMapStateHistory;
                Eegeo_DELETE m_pVisualMapModel;
            }
            
            IVisualMapService& VisualMapModule::GetVisualMapService() const
            {
                return *m_pVisualMapService;
            }
        }
    }
}