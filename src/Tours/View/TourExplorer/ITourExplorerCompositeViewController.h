// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                class ITourExplorerCompositeViewController
                {
                public:
                    virtual ~ITourExplorerCompositeViewController() { }
                    
                    virtual void OpenTourExplorer(const SdkModel::TourModel& tourModel, const int startAtCard) = 0;
                    
                    virtual void CloseTourExplorer() = 0;
                };
            }
        }
    }
}
