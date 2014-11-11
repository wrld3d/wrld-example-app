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
#include "NativeToUiMessageBus.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        class SearchResultOnMapInFocusController : public ISearchResultOnMapInFocusController, private Eegeo::NonCopyable
        {
        private:
            SearchResultOnMapModel& m_searchResultOnMapModel;
            ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
            WorldPins::IWorldPinsService& m_worldPinsService;
            Eegeo::Camera::RenderCamera& m_renderCamera;
            Search::SearchResultModel* m_pLastFocussedModel;
            
        public:
            SearchResultOnMapInFocusController(
				SearchResultOnMapModel& searchResultOnMapModel,
				ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus,
				WorldPins::IWorldPinsService& worldPinsService,
				Eegeo::Camera::RenderCamera& renderCamera);
            
            ~SearchResultOnMapInFocusController();
            
            void Update(float deltaSeconds, const Eegeo::dv3& ecefInterestPoint);
        };
    }
}
