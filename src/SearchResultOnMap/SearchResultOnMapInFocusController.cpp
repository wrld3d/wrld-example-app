// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <limits>
#include "SearchResultOnMapInFocusController.h"
#include "IWorldPinsService.h"
#include "ISearchResultOnMapInFocusViewModel.h"
#include "VectorMath.h"
#include "IInterestPointProvider.h"
#include "RenderCamera.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        SearchResultOnMapInFocusController::SearchResultOnMapInFocusController(SearchResultOnMapModel& searchResultOnMapModel,
                                                                               ISearchResultOnMapInFocusViewModel& searchResultOnMapInFocusViewModel,
                                                                               WorldPins::IWorldPinsService& worldPinsService,
                                                                               Eegeo::Camera::RenderCamera& renderCamera)
        : m_searchResultOnMapModel(searchResultOnMapModel)
        , m_searchResultOnMapInFocusViewModel(searchResultOnMapInFocusViewModel)
        , m_worldPinsService(worldPinsService)
        , m_renderCamera(renderCamera)
        , m_pLastFocussedModel(NULL)
        {
            
        }
        
        SearchResultOnMapInFocusController::~SearchResultOnMapInFocusController()
        {
            
        }
        
        void SearchResultOnMapInFocusController::Update(float deltaSeconds, const Eegeo::dv3& ecefInterestPoint)
        {
            Search::SearchResultModel* pClosest = NULL;
            double minDistanceSq = std::numeric_limits<double>::max();
            Eegeo::v2 closestScreenPinLocation;
            
            for(SearchResultOnMapModel::mapIt it = m_searchResultOnMapModel.begin();
                it != m_searchResultOnMapModel.end();
                ++ it)
            {
                Search::SearchResultModel& searchResultModel = *it->first;
                ExampleApp::WorldPins::WorldPinItemModel& worldPinItemModel = it->second;
                
                Eegeo::dv3 ecefPinLocation;
                Eegeo::v2 screenPinLocation;
                
                m_worldPinsService.GetPinEcefAndScreenLocations(worldPinItemModel,
                                                                ecefPinLocation,
                                                                screenPinLocation);
                
                Eegeo::v3 cameraLocal = (ecefPinLocation - m_renderCamera.GetEcefLocation()).ToSingle();
                Eegeo::v3 screenPos;
                m_renderCamera.Project(cameraLocal, screenPos);
                screenPinLocation.Set(screenPos.GetX(), screenPos.GetY());
                
                double distanceToFocusSq = (ecefInterestPoint - ecefPinLocation).LengthSq();
                
                if(distanceToFocusSq < minDistanceSq && worldPinItemModel.IsVisible())
                {
                    pClosest = &searchResultModel;
                    minDistanceSq = distanceToFocusSq;
                    closestScreenPinLocation = screenPinLocation;
                }
            }
            
            if(m_pLastFocussedModel != pClosest)
            {
                m_pLastFocussedModel = pClosest;
                
                if(m_pLastFocussedModel != NULL)
                {
                    m_searchResultOnMapInFocusViewModel.Open(*m_pLastFocussedModel, closestScreenPinLocation);
                }
                else
                {
                    m_searchResultOnMapInFocusViewModel.Close();
                }
            }
            else
            {
                if(m_pLastFocussedModel != NULL)
                {
                    m_searchResultOnMapInFocusViewModel.UpdateScreenLocation(closestScreenPinLocation);
                }
            }
        }
    }
}
