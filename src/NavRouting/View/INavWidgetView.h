// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class INavWidgetView
            {
            public:
                virtual ~INavWidgetView() { };

                virtual void Show() = 0;

                virtual void Hide() = 0;

                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
