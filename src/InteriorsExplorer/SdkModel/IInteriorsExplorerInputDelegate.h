// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AppInterface.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class IInteriorsExplorerInputDelegate
            {
            public:
                virtual ~IInteriorsExplorerInputDelegate()
                {

                }

                virtual bool HandleTouchTap(const AppInterface::TapData& tapData) = 0;
            };
        }
    }
}
