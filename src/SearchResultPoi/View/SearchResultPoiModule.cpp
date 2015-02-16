// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiModule.h"
#include "SearchResultPoiViewModel.h"
#include "SearchResultPoiMyPinService.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            SearchResultPoiModule::SearchResultPoiModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                         Reaction::View::IReactionControllerModel& reactionControllerModel,
                                                         MyPins::SdkModel::IMyPinsService& myPinsService,
                                                         MyPins::SdkModel::IMyPinsRepository& myPinsRepository,
                                                         CategorySearch::ISearchResultIconCategoryMapper& searchResultIconCategoryMapper,
                                                         ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pSearchResultPoiViewModel = Eegeo_NEW(SearchResultPoiViewModel)(identityProvider.GetNextIdentity(),
                                                                                  reactionControllerModel);
                
                m_pSearchResultPoiMyPinService = Eegeo_NEW(SdkModel::SearchResultPoiMyPinService)(myPinsService,
                                                                                                  myPinsRepository,
                                                                                                  searchResultIconCategoryMapper);
                
                m_pSearchResultPoiPinToggledMessageHandler = Eegeo_NEW(SdkModel::SearchResultPoiPinToggledMessageHandler)(*m_pSearchResultPoiMyPinService,
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
