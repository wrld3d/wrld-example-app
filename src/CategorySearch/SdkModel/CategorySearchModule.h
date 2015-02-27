// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICategorySearchModule.h"
#include "Types.h"
#include "Search.h"
#include "Menu.h"
#include "CategorySearchSelectedMessageHandler.h"
#include "BidirectionalBus.h"
#include "CategorySearchModel.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace SdkModel
        {
            class CategorySearchModule : public ICategorySearchModule, private Eegeo::NonCopyable
            {
            public:
                CategorySearchModule(const std::vector<CategorySearch::View::CategorySearchModel>& categorySearchModels,
                                     Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                     Menu::View::IMenuViewModel& menuViewModel,
                                     ExampleAppMessaging::TMessageBus& messageBus);

                ~CategorySearchModule();

                Menu::View::IMenuModel& GetCategorySearchMenuModel() const;

                View::ICategorySearchRepository& GetCategorySearchRepository() const;
                
                ISearchResultIconCategoryMapper& GetSearchResultIconCategoryMapper() const;

            private:
                Menu::View::IMenuModel* m_pMenuModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
                View::ICategorySearchRepository* m_pCategorySearchRepository;
                CategorySearchSelectedMessageHandler* m_pCategorySearchSelectedMessageHandler;
                ISearchResultIconCategoryMapper* m_pSearchResultIconCategoryMapper;
            };
        }
    }
}
