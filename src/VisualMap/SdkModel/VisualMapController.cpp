// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "VisualMapController.h"
#include "IVisualMapModel.h"
#include "IVisualMapStateHistory.h"

#include "ICityThemesService.h"
#include "ICityThemesUpdater.h"
#include "EnvironmentFlatteningService.h"

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            VisualMapController::VisualMapController(IVisualMapModel& visualMapModel,
                                                     IVisualMapStateHistory& visualMapStateHistory,
                                                     Eegeo::Resources::CityThemes::ICityThemesService& themesService,
                                                     Eegeo::Resources::CityThemes::ICityThemesUpdater& themesUpdater,
                                                     Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService)
            : m_visualMapModel(visualMapModel)
            , m_visualMapStateHistory(visualMapStateHistory)
            , m_themesService(themesService)
            , m_themesUpdater(themesUpdater)
            , m_environmentFlatteningService(environmentFlatteningService)
            , m_onVisualMapModelChanged(this, &VisualMapController::OnVisualMapModelChanged)
            {
                m_visualMapModel.AddVisualMapStateChangedCallback(m_onVisualMapModelChanged);
            }
            
            VisualMapController::~VisualMapController()
            {
                m_visualMapModel.RemoveVisualMapStateChangedCallback(m_onVisualMapModelChanged);
            }
            
            void VisualMapController::OnVisualMapModelChanged(const VisualMapState& previousState, const bool& storePreviousState)
            {
                if (storePreviousState)
                {
                    m_visualMapStateHistory.Push(previousState);
                }
                
                VisualMapState currentState = m_visualMapModel.GetVisualMapState();
                
                m_environmentFlatteningService.SetIsFlattened(currentState.IsFlattened());

                m_themesUpdater.SetThemeMustContain(currentState.GetTheme());
                m_themesService.RequestTransitionToState(currentState.GetState(), 1);
            }
        }
    }
}