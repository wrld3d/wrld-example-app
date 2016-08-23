// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ITagSearchModule.h"
#include "Types.h"
#include "Search.h"
#include "Menu.h"
#include "TagSearchSelectedMessageHandler.h"
#include "BidirectionalBus.h"
#include "TagSearchModel.h"
#include "IMetricsService.h"
#include "IMenuReactionModel.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "TagSearchRepository.h"
#include "SearchResultIconKeyMapper.h"
#include "TagSearchRepositoryObserver.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace SdkModel
        {
            class TagSearchModule : public ITagSearchModule, private Eegeo::NonCopyable
            {
            public:
                static TagSearchModule* Create(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                               ExampleAppMessaging::TMessageBus& messageBus,
                                               Metrics::IMetricsService& metricsService);

                TagSearchModule(
                        Menu::View::MenuModel* pModel,
                        Menu::View::MenuOptionsModel* pOptionsModel,
                        View::TagSearchRepository* pRepository,
                        TagSearch::SdkModel::TagSearchRepositoryObserver* pRepositoryObserver,
                        TagSearchSelectedMessageHandler* pHandler,
                        ExampleApp::TagSearch::SearchResultIconKeyMapper* pMapper);

                ~TagSearchModule();

                Menu::View::IMenuModel& GetTagSearchMenuModel() const override;

                Menu::View::IMenuOptionsModel& GetTagSearchMenuOptionsModel() const override;

                View::ITagSearchRepository& GetTagSearchRepository() const override;
                
                ISearchResultIconKeyMapper& GetSearchResultIconKeyMapper() const override;

            private:
                Menu::View::IMenuModel* m_pMenuModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
                View::ITagSearchRepository* m_pTagSearchRepository;
                TagSearchRepositoryObserver* m_pTagSearchRepositoryObserver;
                TagSearchSelectedMessageHandler* m_pTagSearchSelectedMessageHandler;
                ISearchResultIconKeyMapper* m_pSearchResultIconKeyMapper;
            };
        }
    }
}
