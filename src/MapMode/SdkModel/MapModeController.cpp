// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MapModeController.h"
#include "IMapModeModel.h"
#include "EnvironmentFlatteningService.h"
#include "IWeatherController.h"

namespace ExampleApp
{
    namespace MapMode
    {
        namespace SdkModel
        {
            MapModeController::MapModeController(IMapModeModel& mapModeModel,
                                                 Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                 WeatherMenu::SdkModel::IWeatherController& weatherController)
            : m_mapModeModel(mapModeModel)
            , m_environmentFlatteningService(environmentFlatteningService)
            , m_weatherController(weatherController)
            , m_onMapModeChangedCallback(this, &MapModeController::OnMapModeChanged)
            {
                m_mapModeModel.AddMapModeChangedCallback(m_onMapModeChangedCallback);
            }

            MapModeController::~MapModeController()
            {
                m_mapModeModel.RemoveMapModeChangedCallback(m_onMapModeChangedCallback);
            }

            void MapModeController::OnMapModeChanged()
            {
                if (m_mapModeModel.IsInMapMode())
                {
                    m_environmentFlatteningService.SetIsFlattened(true);
                    m_previousThemeState = m_weatherController.GetState();
                    m_weatherController.SetState("MapMode");
                }
                else
                {
                    Eegeo_ASSERT(!m_previousThemeState.empty());
                    m_environmentFlatteningService.SetIsFlattened(false);
                    m_weatherController.SetState(m_previousThemeState);
                }
            }
        }
    }
}