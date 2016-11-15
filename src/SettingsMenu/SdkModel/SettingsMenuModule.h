// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>

#include "AboutPage.h"
#include "BidirectionalBus.h"
#include "IIdentity.h"
#include "IMetricsService.h"
#include "ISettingsMenuModule.h"
#include "Menu.h"
#include "Options.h"
#include "Reaction.h"
#include "Search.h"
#include "Types.h"
#include "Weather.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace SdkModel
        {
            class SettingsMenuModule: public ISettingsMenuModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuModel* m_pModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
                Menu::View::IMenuViewModel* m_pViewModel;
                std::vector<Menu::View::IMenuSectionViewModel*> m_sections;
                Menu::View::IMenuModel* m_pAboutMenuModel;
                Menu::View::IMenuOptionsModel* m_pAboutMenuOptionsModel;
                Menu::View::IMenuModel* m_pOptionsMenuModel;
                Menu::View::IMenuOptionsModel* m_pOptionsMenuOptionsModel;

            public:
                SettingsMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                   Reaction::View::IReactionControllerModel& reactionControllerModel,
                                   AboutPage::View::IAboutPageViewModel& aboutPageViewModel,
                                   Options::View::IOptionsViewModel& optionsViewModel,
                                   Menu::View::IMenuModel& weatherMenuModel);

                ~SettingsMenuModule();

                void AddMenuSection(const std::string& name,
                                    Menu::View::IMenuModel& menuModel,
                                    bool isExpandable);
                
                Menu::View::IMenuModel& GetSettingsMenuModel() const;

                Menu::View::IMenuOptionsModel& GetSettingsMenuOptionsModel() const;

                Menu::View::IMenuViewModel& GetSettingsMenuViewModel() const;
            };
        }
    }
}
