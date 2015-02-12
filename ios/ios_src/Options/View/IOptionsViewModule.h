// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "OptionsViewIncludes.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            class IOptionsViewModule
            {
            public:
                virtual ~IOptionsViewModule() { }

                virtual OptionsController& GetOptionsController() const = 0;

                virtual OptionsView& GetOptionsView() const = 0;
            };
        }
    }
}
