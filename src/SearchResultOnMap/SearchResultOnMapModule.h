// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Search.h"
#include "ISearchResultOnMapModule.h"
#include "SearchResultOnMap.h"
#include "SearchResultPoi.h"
#include "WorldPins.h"
#include "Location.h"
#include "Modality.h"
#include "IIdentity.h"
#include "Rendering.h"
#include "Camera.h"
#include "SearchResultOnMapScaleController.h"
#include "SearchResultOnMapInFocusViewModel.h"
#include "SearchResultOnMapModalityObserver.h"
#include "SearchResultOnMapInFocusObserver.h"
#include "UiToNativeMessageBus.h"
#include "NativeToUiMessageBus.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        class SearchResultOnMapModule: public ISearchResultOnMapModule, private Eegeo::NonCopyable
        {
        private:
            ISearchResultOnMapModel* m_pSearchResultOnMapModel;
            SearchResultOnMapInFocusViewModel* m_pSearchResultOnMapInFocusViewModel;
            ISearchResultOnMapInFocusController* m_pSearchResultOnMapInFocusController;
            SearchResultOnMapScaleController* m_pSearchResultOnMapScaleController;
            ISearchResultOnMapFactory* m_pSearchResultOnMapFactory;
            ISearchResultOnMapIconCategoryMapper* m_pSearchResultOnMapIconCategoryMapper;
            SearchResultOnMapModalityObserver* m_pSearchResultOnMapModalityObserver;
            SearchResultOnMapInFocusObserver* m_pSearchResultOnMapInFocusObserver;
            
        public:
            SearchResultOnMapModule(Search::ISearchResultRepository& searchResultRepository,
                                    SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel,
                                    WorldPins::IWorldPinsService& worldPinsService,
                                    Eegeo::Helpers::IIdentityProvider& identityProvider,
                                    const Eegeo::Rendering::ScreenProperties& screenProperties,
                                    Eegeo::Camera::RenderCamera& renderCamera,
                                    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                    ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);
            
            ~SearchResultOnMapModule();
            
            ISearchResultOnMapModel& GetSearchResultOnMapModel() const;
            
            ISearchResultOnMapInFocusViewModel& GetSearchResultOnMapInFocusViewModel() const;
            
            ISearchResultOnMapInFocusController& GetSearchResultOnMapInFocusController() const;
            
            ISearchResultOnMapScaleController& GetSearchResultOnMapScaleController() const;
            
            ScreenControlViewModel::IScreenControlViewModel& GetScreenControlViewModel() const;
        };
    }
}
