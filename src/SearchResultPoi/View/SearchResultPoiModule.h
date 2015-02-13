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
#include "BidirectionalBus.h"
#include "CategorySearch.h"

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
                SearchResultPoiViewModel* m_pSearchResultPoiViewModel;
                SdkModel::SearchResultPoiPinToggledMessageHandler* m_pSearchResultPoiPinToggledMessageHandler;

            public:
                SearchResultPoiModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                      Reaction::View::IReactionControllerModel& reactionControllerModel,
                                      MyPins::SdkModel::IMyPinsService& myPinsService,
                                      MyPins::SdkModel::IMyPinsRepository& myPinsRepository,
                                      CategorySearch::ISearchResultIconCategoryMapper& searchResultIconCategoryMapper,
                                      ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultPoiModule();

                ISearchResultPoiViewModel& GetSearchResultPoiViewModel() const;

                OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const;
            };
        }
    }
}
