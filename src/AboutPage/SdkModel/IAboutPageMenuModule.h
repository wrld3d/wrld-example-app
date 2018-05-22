// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace SdkModel
        {
            class IAboutPageMenuModule
            {
            public:
                virtual ~IAboutPageMenuModule() { }

                virtual Menu::View::IMenuModel& GetAboutPageMenuModel() const = 0;
            };
        }
    }
}
