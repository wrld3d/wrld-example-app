// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "TourExplorerViewIncludes.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                class ITourExplorerViewModule
                {
                public:
                    
                    virtual ~ITourExplorerViewModule() { }
                    
                    virtual TourExplorerView& GetTourExplorerView() const = 0;
                };
            }
        }
    }
}
