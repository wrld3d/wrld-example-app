// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchModule.h"
#include "SearchResultRepository.h"
#include "SearchResultModel.h"
#include "SearchQueryPerformer.h"
#include "SearchRefreshService.h"
#include "DecartaSearchJsonParser.h"
#include "DecartaSearchService.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            SearchModule::SearchModule(const std::string& searchApiKey,
                                       Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory,
                                       Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                       Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& cameraController,
                                       CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionsController,
                                       ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pSearchResultRepository = Eegeo_NEW(SearchResultRepository)();

                m_pSearchResultParser = Eegeo_NEW(Decarta::DecartaSearchJsonParser);

                m_pSearchService = Eegeo_NEW(Decarta::DecartaSearchService)(searchApiKey,
                                   *m_pSearchResultParser,
                                   urlEncoder,
                                   webLoadRequestFactory);

                m_pSearchQueryPerformer = Eegeo_NEW(SearchQueryPerformer)(*m_pSearchService,
                                          *m_pSearchResultRepository,
                                          cameraController);

                m_pSearchRefreshService = Eegeo_NEW(SearchRefreshService)(*m_pSearchService,
                                          *m_pSearchQueryPerformer,
                                          cameraTransitionsController,
                                          1.f,
                                          500.f);

                m_pSearchQueryObserver = Eegeo_NEW(SearchQueryObserver)(
                                             *m_pSearchService,
                                             *m_pSearchQueryPerformer,
                                             messageBus
                                         );
            }

            SearchModule::~SearchModule()
            {
                Eegeo_DELETE m_pSearchQueryObserver;
                Eegeo_DELETE m_pSearchRefreshService;
                Eegeo_DELETE m_pSearchQueryPerformer;
                Eegeo_DELETE m_pSearchService;
                Eegeo_DELETE m_pSearchResultParser;
                Eegeo_DELETE m_pSearchResultRepository;
            }

            ISearchService& SearchModule::GetSearchService() const
            {
                return *m_pSearchService;
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
        }
    }
}
