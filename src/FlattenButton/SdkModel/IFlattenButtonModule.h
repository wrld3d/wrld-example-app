// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "FlattenButton.h"
#include "ScreenControlViewModelIncludes.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace SdkModel
        {
            class IFlattenButtonModule
            {
            public:
                virtual ~IFlattenButtonModule() { }

                virtual IFlattenButtonModel& GetFlattenButtonModel() const = 0;

                virtual View::IFlattenButtonViewModel& GetFlattenButtonViewModel() const = 0;

                virtual ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const = 0;
            };
        }
    }
}
