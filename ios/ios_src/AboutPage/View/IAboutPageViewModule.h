// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AboutPageViewIncludes.h"

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

                virtual AboutPageController& GetAboutPageController() const = 0;

                virtual AboutPageView& GetAboutPageView() const = 0;
            };
        }
    }
}
