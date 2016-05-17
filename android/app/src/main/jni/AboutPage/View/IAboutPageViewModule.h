// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AboutPageViewIncludes.h"
#include "AboutPage.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            class IAboutPageViewModule
            {
            public:
                virtual ~IAboutPageViewModule() { }

                virtual AboutPageView& GetAboutPageView() const = 0;
                virtual AboutPageController& GetAboutPageController() const = 0;
            };
        }
    }
}
