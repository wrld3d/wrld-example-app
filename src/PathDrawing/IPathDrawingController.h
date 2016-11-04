// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Route.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        class IPathDrawingController
        {
        public:
            
            virtual ~IPathDrawingController() {}
            
            virtual void Update(float dt){};
            
            virtual bool IsRouteCreated() = 0;
            
            virtual std::vector<Eegeo::Routes::Route*>& GetCreatedRoutes() = 0;
            
            virtual void RemoveRoutePlan() = 0;

            
        };
    }
}
