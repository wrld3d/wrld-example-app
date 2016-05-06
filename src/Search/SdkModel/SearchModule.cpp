// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchModule.h"
#include "SearchResultRepository.h"
#include "SearchResultModel.h"
#include "SearchQueryPerformer.h"
#include "SearchRefreshService.h"
#include "SearchResultMyPinsService.h"
#include "MyPinsSearchResultRefreshService.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            SearchModule::SearchModule(ISearchService& exteriorSearchService,
                                       Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& cameraController,
                                       CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionsController,
                                       Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                       ExampleAppMessaging::TMessageBus& messageBus,
                                       ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus)
            {
                m_pSearchResultRepository = Eegeo_NEW(SearchResultRepository)();
                
                m_pSearchResultMyPinsService = Eegeo_NEW(MyPins::SearchResultMyPinsService)(sdkModelDomainEventBus);
                
                m_pMyPinsSearchResultRefreshService = Eegeo_NEW(MyPins::MyPinsSearchResultRefreshService)(*m_pSearchResultMyPinsService,
                                                                                                          exteriorSearchService);

                m_pSearchQueryPerformer = Eegeo_NEW(SearchQueryPerformer)(exteriorSearchService,
                                                                          *m_pSearchResultRepository,
                                                                          cameraController);

                m_pSearchRefreshService = Eegeo_NEW(SearchRefreshService)(exteriorSearchService,
                                          *m_pSearchQueryPerformer,
                                          cameraTransitionsController,
                                          interiorInteractionModel,
                                          1.f,
                                          100.f,
                                          1100.f,
                                          50.f);

                m_pSearchQueryObserver = Eegeo_NEW(SearchQueryObserver)(exteriorSearchService,
                                                                        *m_pSearchQueryPerformer,
                                                                        messageBus);
            }

            SearchModule::~SearchModule()
            {
                Eegeo_DELETE m_pSearchQueryObserver;
                Eegeo_DELETE m_pSearchRefreshService;
                Eegeo_DELETE m_pSearchQueryPerformer;
                Eegeo_DELETE m_pMyPinsSearchResultRefreshService;
                Eegeo_DELETE m_pSearchResultMyPinsService;
                Eegeo_DELETE m_pSearchResultRepository;
            }
            
            ISearchResultRepository& SearchModule::GetSearchResultRepository() const
            {
                return *m_pSearchResultRepository;
            }

            ISearchQueryPerformer& SearchModule::GetSearchQueryPerformer() const
            {
                return *m_pSearchQueryPerformer;
            }

            ISearchRefreshService& SearchModule::GetSearchRefreshService() const
            {
                return *m_pSearchRefreshService;
            }
            
            MyPins::ISearchResultMyPinsService& SearchModule::GetSearchResultMyPinsService() const
            {
                return *m_pSearchResultMyPinsService;
            }
            
            MyPins::IMyPinsSearchResultRefreshService& SearchModule::GetMyPinsSearchResultRefreshService() const
            {
                return *m_pMyPinsSearchResultRefreshService;
            }
        }
    }
}
