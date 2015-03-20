// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiModule.h"
#include "SearchResultPoiViewModel.h"
#include "SearchResultPoiMyPinService.h"
#include "SearchResultPoiViewImageFetcher.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            SearchResultPoiModule::SearchResultPoiModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                         Reaction::View::IReactionControllerModel& reactionControllerModel,
                                                         MyPins::SdkModel::IMyPinsService& myPinsService,
                                                         Search::SdkModel::MyPins::ISearchResultMyPinsService& searchResultMyPinsService,
                                                         CategorySearch::ISearchResultIconCategoryMapper& searchResultIconCategoryMapper,
                                                         Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                         ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pSearchResultPoiViewModel = Eegeo_NEW(SearchResultPoiViewModel)(identityProvider.GetNextIdentity(),
                                                                                  reactionControllerModel);
                
                m_pSearchResultPoiMyPinService = Eegeo_NEW(SdkModel::SearchResultPoiMyPinService)(myPinsService,
                                                                                                  searchResultMyPinsService,
                                                                                                  searchResultIconCategoryMapper);
                
                m_pSearchResultPoiPinToggledMessageHandler = Eegeo_NEW(SdkModel::SearchResultPoiPinToggledMessageHandler)(*m_pSearchResultPoiMyPinService,
                                                                                                                          messageBus);
                
                m_pSearchResultPoiViewImageFetcher = Eegeo_NEW(SdkModel::SearchResultPoiViewImageFetcher)(webRequestFactory,
                                                                                                          messageBus);
                
                m_pSearchResultPoiViewOpenedMessageHandler = Eegeo_NEW(SdkModel::SearchResultPoiViewOpenedMessageHandler)(*m_pSearchResultPoiViewImageFetcher,
                                                                                                                          messageBus);
            }

            SearchResultPoiModule::~SearchResultPoiModule()
            {
                Eegeo_DELETE m_pSearchResultPoiPinToggledMessageHandler;
                Eegeo_DELETE m_pSearchResultPoiMyPinService;
                Eegeo_DELETE m_pSearchResultPoiViewModel;
            }

            ISearchResultPoiViewModel& SearchResultPoiModule::GetSearchResultPoiViewModel() const
            {
                return *m_pSearchResultPoiViewModel;
            }

            OpenableControl::View::IOpenableControlViewModel& SearchResultPoiModule::GetObservableOpenableControl() const
            {
                return m_pSearchResultPoiViewModel->GetOpenableControl();
            }
        }
    }
}
