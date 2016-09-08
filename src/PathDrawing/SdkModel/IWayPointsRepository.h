// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IRepositoryModel.h"
#include "WayPoint.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {
            class IWayPointsRepository : public Repository::IRepositoryModel<WayPoint*>
            {
            };
        }
    }
}
