// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "Types.h"
#include "Menu.h"
#include "ISecondaryMenuModule.h"
#include "IIdentity.h"
#include "Reaction.h"
#include "Search.h"
#include "SecondaryMenu.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace SdkModel
        {
            class SecondaryMenuModule: public ISecondaryMenuModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuModel* m_pModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
                Menu::View::IMenuViewModel* m_pViewModel;
                std::vector<Menu::View::IMenuSectionViewModel*> m_sections;
                PerformedSearchMessageHandler* m_pPerformedSearchMessageHandler;

            public:
                SecondaryMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                    Reaction::View::IReactionControllerModel& reactionControllerModel,
                                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                    ExampleAppMessaging::TMessageBus& messageBus);

                ~SecondaryMenuModule();

                void AddMenuSection(const std::string& name, const std::string& icon, Menu::View::IMenuModel& menuModel, bool isExpandable);

                Menu::View::IMenuModel& GetSecondaryMenuModel() const;

                Menu::View::IMenuOptionsModel& GetSecondaryMenuOptionsModel() const;

                Menu::View::IMenuViewModel& GetSecondaryMenuViewModel() const;
            };
        }
    }
}
