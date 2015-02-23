// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IOpenableControlViewModel.h"
#include "AboutPage.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            class IAboutPageModule
            {
            public:
                virtual ~IAboutPageModule() { }

                virtual IAboutPageViewModel& GetAboutPageViewModel() const = 0;

                virtual OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const = 0;
            };
        }
    }
}
