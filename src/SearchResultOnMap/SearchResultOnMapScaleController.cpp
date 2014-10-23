// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <limits>
#include "SearchResultOnMapScaleController.h"
#include "IWorldPinsService.h"
#include "ISearchResultOnMapInFocusViewModel.h"
#include "IModalityModel.h"
#include "ScreenProperties.h"
#include "RenderCamera.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        SearchResultOnMapScaleController::SearchResultOnMapScaleController(SearchResultOnMapModel& searchResultOnMapModel,
                                                                           WorldPins::IWorldPinsService& worldPinsService,
                                                                           Modality::IModalityModel& modalityModel,
                                                                           const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                                           Eegeo::Camera::RenderCamera& renderCamera)
        : m_searchResultOnMapModel(searchResultOnMapModel)
        , m_worldPinsService(worldPinsService)
        , m_modalityModel(modalityModel)
        , m_screenProperties(screenProperties)
        , m_renderCamera(renderCamera)
        , m_globalScale(1.f)
        , m_pModalityChangedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<SearchResultOnMapScaleController>)(this, &SearchResultOnMapScaleController::HandleModalityChanged))
        {
            m_modalityModel.InsertModalityChangedCallback(*m_pModalityChangedCallback);
        }
        
        SearchResultOnMapScaleController::~SearchResultOnMapScaleController()
        {
            m_modalityModel.RemoveModalityChangedCallback(*m_pModalityChangedCallback);
            Eegeo_DELETE m_pModalityChangedCallback;
        }
        
        void SearchResultOnMapScaleController::Update(float deltaSeconds)
        {
            for(SearchResultOnMapModel::mapIt it = m_searchResultOnMapModel.begin();
                it != m_searchResultOnMapModel.end();
                ++ it)
            {
                Search::SearchResultModel& searchResultModel = *it->first;
                WorldPins::WorldPinItemModel& worldPinItemModel = it->second;

                UpdateWorldPin(worldPinItemModel, deltaSeconds);
                float scale = m_globalScale * GetResultScale(searchResultModel) * worldPinItemModel.TransitionStateValue();
                m_worldPinsService.UpdatePinScale(worldPinItemModel, scale);
            }
        }
        
        float SearchResultOnMapScaleController::GetResultScale(Search::SearchResultModel& searchResultModel)
        {
            // todo -- implement any per result scaling here, for example scaling the pins by
            // the popularity or relevance of search results, if data available.
            
            return 1.f;
        }
        
        void SearchResultOnMapScaleController::UpdateWorldPin(WorldPins::WorldPinItemModel& worldPinItemModel, float deltaSeconds)
        {
            Eegeo::v2 screenLocation;
            GetScreenLocation(worldPinItemModel, screenLocation);
            
            const float ratioX = screenLocation.GetX() / m_screenProperties.GetScreenWidth();
            const float ratioY = screenLocation.GetY() / m_screenProperties.GetScreenHeight();
            const bool shouldHide = (ratioX < 0.1f) || (ratioX > 0.9f) || (ratioY < 0.15f) || (ratioY > 0.9f);
            
            if(shouldHide)
            {
                worldPinItemModel.Hide();
            }
            else
            {
                worldPinItemModel.Show();
            }
            
            worldPinItemModel.Update(deltaSeconds);
        }
        
        void SearchResultOnMapScaleController::HandleModalityChanged()
        {
            m_globalScale = 1.f - m_modalityModel.GetModality();
        }
        
        void SearchResultOnMapScaleController::GetScreenLocation(const WorldPins::WorldPinItemModel& worldPinItemModel, Eegeo::v2& screenLocation) const
        {
            Eegeo::dv3 ecefLocation;
            m_worldPinsService.GetPinEcefAndScreenLocations(worldPinItemModel, ecefLocation, screenLocation);
            Eegeo::v3 cameraLocal = (ecefLocation - m_renderCamera.GetEcefLocation()).ToSingle();
            Eegeo::v3 screenPos;
            m_renderCamera.Project(cameraLocal, screenPos);
            screenLocation.Set(screenPos.GetX(), screenPos.GetY());
        }
    }
}
