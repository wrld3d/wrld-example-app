// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MapModeController.h"
#include "IMapModeModel.h"
#include "IVisualMapService.h"
#include "VisualMapState.h"

namespace ExampleApp
{
    namespace MapMode
    {
        namespace SdkModel
        {
            MapModeController::MapModeController(IMapModeModel& mapModeModel,
                                                 VisualMap::SdkModel::IVisualMapService& visualMapService)
            : m_mapModeModel(mapModeModel)
            , m_visualMapService(visualMapService)
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
                    const VisualMap::SdkModel::VisualMapState& currentState = m_visualMapService.GetCurrentVisualMapState();
                    m_visualMapService.SetVisualMapState(currentState.GetTheme(), "MapMode", true);
                }
                else
                {
                    m_visualMapService.RestorePreviousMapState();
                }
            }
        }
    }
}