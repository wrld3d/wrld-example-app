// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IOpenableControlViewModel.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        class IAboutPageModule
        {
        public:
            virtual ~IAboutPageModule() { }
            
            virtual IAboutPageModel& GetAboutPageModel() const = 0;
            
            virtual IAboutPageViewModel& GetAboutPageViewModel() const = 0;
            
            virtual OpenableControlViewModel::IOpenableControlViewModel& GetObservableOpenableControl() const = 0;
        };
    }
}
