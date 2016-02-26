// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchMenuModule.h"

#include <vector>

#include "BidirectionalBus.h"
#include "IIdentity.h"
#include "Metrics.h"
#include "Reaction.h"
#include "Search.h"
#include "SearchMenu.h"
#include "Types.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace SdkModel
        {
            class SearchMenuModule : public ISearchMenuModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuModel* m_pMenuModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
                Menu::View::IMenuViewModel* m_pMenuViewModel;
                Menu::View::IMenuSectionViewModel* m_pSearchSectionViewModel;
                SearchMenuPerformedSearchMessageHandler* m_pPerformedSearchMessageHandler;
                std::vector<Menu::View::IMenuSectionViewModel*> m_sections;
                
            public:
                SearchMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                 ExampleApp::Reaction::View::IReactionControllerModel& reactionControllerModel,
                                 Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                 ExampleAppMessaging::TMessageBus& messageBus,
                                 Metrics::IMetricsService& metricsService);
                
                ~SearchMenuModule();
                
                void SetSearchSection(const std::string& name,
                                      Menu::View::IMenuModel& menuModel);
                
                void AddMenuSection(const std::string& name,
                                    Menu::View::IMenuModel& menuModel,
                                    bool isExpandable);
                
                Menu::View::IMenuModel& GetSearchMenuModel() const;
                
                Menu::View::IMenuOptionsModel& GetSearchMenuOptionsModel() const;
                
                Menu::View::IMenuViewModel& GetSearchMenuViewModel() const;
                
                Menu::View::IMenuSectionViewModel& GetSearchSectionViewModel() const;
            };
        }
    }
}