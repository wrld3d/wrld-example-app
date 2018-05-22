// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>

#include "IOptionsMenuModule.h"
#include "Options.h"
#include "BidirectionalBus.h"
#include "IIdentity.h"
#include "IMetricsService.h"
#include "Menu.h"
#include "Reaction.h"
#include "Search.h"
#include "Types.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            class OptionsMenuModule: public IOptionsMenuModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuModel* m_pOptionsMenuModel;
                Menu::View::IMenuOptionsModel* m_pOptionsMenuOptionsModel;

            public:
                OptionsMenuModule(Menu::View::IMenuViewModel& menuViewModel,
                                   Options::View::IOptionsViewModel& OptionsViewModel);

                ~OptionsMenuModule();

                Menu::View::IMenuModel& GetOptionsMenuModel() const;
            };
        }
    }
}
