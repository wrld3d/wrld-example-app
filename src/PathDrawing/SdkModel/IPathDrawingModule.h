// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlViewModel.h"
#include "WayPointsRepository.h"
#include "IPathDrawingController.h"
namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {
            class IPathDrawingModule
            {
            public:
                virtual ~IPathDrawingModule() { }

                virtual IWayPointsRepository& GetWayPointsRepository() const = 0;
                
                virtual IPathDrawingController& GetPathDrawingController() const = 0;
                
                virtual void Update(float dt) = 0;
            };
        }
    }
}
