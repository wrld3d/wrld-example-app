// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IOpenableControlViewModel.h"
#include "Options.h"

namespace ExampleApp
{
    namespace Options
    {
        class IOptionsModule
        {
        public:
            virtual ~IOptionsModule() { }
            
            virtual View::IOptionsViewModel& GetOptionsViewModel() const = 0;
            
            virtual OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const = 0;
        };
    }
}
