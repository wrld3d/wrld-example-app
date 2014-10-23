// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "SearchResultOnMapModel.h"
#include "WorldPins.h"
#include "SearchResultOnMap.h"
#include "ISearchResultOnMapInFocusController.h"
#include "VectorMathDecl.h"
#include "Location.h"
#include "Camera.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        class SearchResultOnMapInFocusController : public ISearchResultOnMapInFocusController, private Eegeo::NonCopyable
        {
        private:
            SearchResultOnMapModel& m_searchResultOnMapModel;
            ISearchResultOnMapInFocusViewModel& m_searchResultOnMapInFocusViewModel;
            WorldPins::IWorldPinsService& m_worldPinsService;
            Search::SearchResultModel* m_pLastFocussedModel;
            Eegeo::Camera::RenderCamera& m_renderCamera;
            
        public:
            SearchResultOnMapInFocusController(SearchResultOnMapModel& searchResultOnMapModel,
                                               ISearchResultOnMapInFocusViewModel& searchResultOnMapInFocusViewModel,
                                               WorldPins::IWorldPinsService& worldPinsService,
                                               Eegeo::Camera::RenderCamera& renderCamera);
            
            ~SearchResultOnMapInFocusController();
            
            void Update(float deltaSeconds, const Eegeo::dv3& ecefInterestPoint);
        };
    }
}
