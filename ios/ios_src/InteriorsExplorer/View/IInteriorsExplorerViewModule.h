// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InteriorsExplorerViewIncludes.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class IInteriorsExplorerViewModule : public Eegeo::NonCopyable
            {
            public:
                virtual ~IInteriorsExplorerViewModule() {}
                
                virtual InteriorsExplorerController& GetController() const = 0;
                
                virtual InteriorsExplorerView& GetView() const = 0;
                
                virtual InteriorsExplorerTutorialView& GetTutorialView() const = 0;
            };
        }
    }
}