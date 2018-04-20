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
#include "Types.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace SdkModel
        {
            class SettingsMenuModule: public ISettingsMenuModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuModel*        m_pAboutMenuModel;
                Menu::View::IMenuOptionsModel* m_pAboutMenuOptionsModel;

                Menu::View::IMenuModel*        m_pOptionsMenuModel;
                Menu::View::IMenuOptionsModel* m_pOptionsMenuOptionsModel;

            public:
                SettingsMenuModule(Menu::View::IMenuViewModel&           menuViewModel,
                                   AboutPage::View::IAboutPageViewModel& aboutPageViewModel,
                                   Options::View::IOptionsViewModel&     optionsViewModel);

                ~SettingsMenuModule();

                Menu::View::IMenuModel& GetOptionsMenuModel() const;
                
                Menu::View::IMenuModel& GetAboutMenuModel() const;
            };
        }
    }
}
