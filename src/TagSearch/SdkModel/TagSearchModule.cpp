// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TagSearchModule.h"
#include "TagSearchMenuOption.h"
#include "TagSearchMenuOptionFactory.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace SdkModel
        {
            TagSearchModule* TagSearchModule::Create(
                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Metrics::IMetricsService& metricsService)
            {
                auto* pMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                auto* pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*pMenuModel);
                auto* pTagSearchRepository = Eegeo_NEW(View::TagSearchRepository)();

                auto* pTagSearchRepositoryObserver = Eegeo_NEW(TagSearch::SdkModel::TagSearchRepositoryObserver)(
                        *pTagSearchRepository,
                        messageBus);

                auto* pTagSearchSelectedMessageHandler = Eegeo_NEW(TagSearchSelectedMessageHandler)(
                        searchQueryPerformer,
                        messageBus,
                        metricsService);
                
                auto* pSearchResultIconKeyMapper = Eegeo_NEW(SearchResultIconKeyMapper)();

                return Eegeo_NEW(TagSearchModule)(
                        pMenuModel,
                        pMenuOptionsModel,
                        pTagSearchRepository,
                        pTagSearchRepositoryObserver,
                        pTagSearchSelectedMessageHandler,
                        pSearchResultIconKeyMapper);
            }

            TagSearchModule::TagSearchModule(
                    Menu::View::MenuModel* pModel,
                    Menu::View::MenuOptionsModel* pOptionsModel,
                    View::TagSearchRepository* pRepository,
                    TagSearch::SdkModel::TagSearchRepositoryObserver* pRepositoryObserver,
                    TagSearchSelectedMessageHandler* pHandler,
                    ExampleApp::TagSearch::SearchResultIconKeyMapper* pMapper)
            : m_pMenuModel(pModel)
            , m_pMenuOptionsModel(pOptionsModel)
            , m_pTagSearchRepository(pRepository)
            , m_pTagSearchRepositoryObserver(pRepositoryObserver)
            , m_pTagSearchSelectedMessageHandler(pHandler)
            , m_pSearchResultIconKeyMapper(pMapper)
            {

            }

            TagSearchModule::~TagSearchModule()
            {
                Eegeo_DELETE m_pSearchResultIconKeyMapper;
                Eegeo_DELETE m_pTagSearchSelectedMessageHandler;
                Eegeo_DELETE m_pTagSearchRepositoryObserver;
                Eegeo_DELETE m_pTagSearchRepository;
                Eegeo_DELETE m_pMenuOptionsModel;
                Eegeo_DELETE m_pMenuModel;
            }

            Menu::View::IMenuModel& TagSearchModule::GetTagSearchMenuModel() const
            {
                return *m_pMenuModel;
            }

            View::ITagSearchRepository& TagSearchModule::GetTagSearchRepository() const
            {
                return *m_pTagSearchRepository;
            }
            
            ISearchResultIconKeyMapper& TagSearchModule::GetSearchResultIconKeyMapper() const
            {
                return *m_pSearchResultIconKeyMapper;
            }

            Menu::View::IMenuOptionsModel& TagSearchModule::GetTagSearchMenuOptionsModel() const
            {
                return *m_pMenuOptionsModel;
            }
        }
    }
}
