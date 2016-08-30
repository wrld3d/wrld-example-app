// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchResultSectionOrder.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include <memory>

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            class SearchResultSectionMenuModel : public Menu::View::MenuModel
            {
            };
            
            class SearchResultSectionOptionsModel : public Menu::View::MenuOptionsModel
            {
            public:
                SearchResultSectionOptionsModel(const std::shared_ptr<SearchResultSectionMenuModel>& menuModel) : Menu::View::MenuOptionsModel(*menuModel)
                {
                }
            };
            
            class SearchResultSectionOrder : public ISearchResultSectionOrder
            {
            public:
                bool operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b);
            };
        }
    }
}