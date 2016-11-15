// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "SearchResultPoi.h"
#include "ISearchResultPoiModule.h"
#include "SearchResultPoiViewModel.h"
#include "IIdentity.h"
#include "Reaction.h"
#include "SearchResultPoiPinToggledMessageHandler.h"
#include "MyPins.h"
#include "Search.h"
#include "BidirectionalBus.h"
#include "TagSearch.h"
#include "SearchResultPoiViewOpenedMessageHandler.h"
#include "ISearchResultPoiViewImageFetcher.h"
#include "Web.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class SearchResultPoiModule: public ISearchResultPoiModule, private Eegeo::NonCopyable
            {
            private:
                SdkModel::ISearchResultPoiMyPinService* m_pSearchResultPoiMyPinService;
                ISearchResultPoiViewModel* m_pSearchResultPoiViewModel;
                SdkModel::SearchResultPoiPinToggledMessageHandler* m_pSearchResultPoiPinToggledMessageHandler;
                SdkModel::SearchResultPoiViewOpenedMessageHandler* m_pSearchResultPoiViewOpenedMessageHandler;
                SdkModel::ISearchResultPoiViewImageFetcher* m_pSearchResultPoiViewImageFetcher;
                
           public:
                SearchResultPoiModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                      Reaction::View::IReactionControllerModel& reactionControllerModel,
                                      MyPins::SdkModel::IMyPinsService& myPinsService,
                                      Search::SdkModel::MyPins::ISearchResultMyPinsService& searchResultMyPinsService,
                                      TagSearch::ISearchResultIconKeyMapper& searchResultIconKeyMapper,
                                      Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory,
                                      ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultPoiModule();

                ISearchResultPoiViewModel& GetSearchResultPoiViewModel() const;

                OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const;
            };
        }
    }
}
