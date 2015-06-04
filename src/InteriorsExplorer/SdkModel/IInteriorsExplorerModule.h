// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ScreenControlViewModelIncludes.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class IInteriorsExplorerModule
            {
            public:
                virtual ~IInteriorsExplorerModule() { }

                virtual View::InteriorsExplorerViewModel& GetInteriorsExplorerViewModel() const = 0;

                virtual ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const = 0;
            };
        }
    }
}