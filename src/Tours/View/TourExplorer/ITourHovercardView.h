// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlView.h"
#include "ICallback.h"
#include "Tours.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourHovercard
            {
                class ITourHovercardView
                {
                public:
                    
                    virtual ~ITourHovercardView() { }
                    
                    virtual void SetCurrentTour(const SdkModel::TourModel& tourModel) = 0;
                };
            }
        }
    }
}
