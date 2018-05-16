// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>

#include "IAboutPageMenuModule.h"
#include "AboutPage.h"
#include "BidirectionalBus.h"
#include "IIdentity.h"
#include "IMetricsService.h"
#include "Menu.h"
#include "Reaction.h"
#include "Search.h"
#include "Types.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace SdkModel
        {
            class AboutPageMenuModule: public IAboutPageMenuModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuModel* m_pAboutPageMenuModel;
                Menu::View::IMenuOptionsModel* m_pAboutPageMenuOptionsModel;

            public:
                AboutPageMenuModule(Menu::View::IMenuViewModel& menuViewModel,
                                   AboutPage::View::IAboutPageViewModel& aboutPageViewModel);

                ~AboutPageMenuModule();

                Menu::View::IMenuModel& GetAboutPageMenuModel() const;
            };
        }
    }
}
