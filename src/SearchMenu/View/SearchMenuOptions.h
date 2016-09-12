// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "MenuViewModel.h"
#include "MenuSectionViewModel.h"
#include "IIdentity.h"
#include "IReactionControllerModel.h"
#include "SearchResultSectionOrder.h"
#include <memory>

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchMenuModel : public Menu::View::MenuModel
            {
            };
            
            class SearchMenuOptionsModel : public Menu::View::MenuOptionsModel
            {
            public:
                SearchMenuOptionsModel(const std::shared_ptr<SearchMenuModel>& searchMenuModel) : Menu::View::MenuOptionsModel(*searchMenuModel)
                {
                }
            };
            
            class SearchMenuViewModel : public Menu::View::MenuViewModel
            {
            public:
                SearchMenuViewModel(const std::shared_ptr<Eegeo::Helpers::IIdentityProvider>& identity,
                                    const std::shared_ptr<Reaction::View::IReactionControllerModel>& reactionControllerModel)
                : Menu::View::MenuViewModel(false, identity->GetNextIdentity(), reactionControllerModel)
                {
                }
            };
            
            class SearchMenuSectionViewModel : public Menu::View::MenuSectionViewModel
            {
            public:
                SearchMenuSectionViewModel(const std::string& name,
                                           const std::string& icon,
                                           const std::shared_ptr<SearchResultSection::View::SearchResultSectionMenuModel>& searchResultSection,
                                           bool isExpandable)
                : Menu::View::MenuSectionViewModel(name, icon, searchResultSection, isExpandable)
                {
                }
            };
        }
    }
}
