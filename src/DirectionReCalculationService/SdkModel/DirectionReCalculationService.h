// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ILocationService.h"
#include "IPathDrawingController.h"


namespace ExampleApp
{
    namespace DirectionReCalculationService
    {
        namespace SdkModel
        {
            class DirectionReCalculationService
            {
            private:
                Eegeo::Location::ILocationService& m_locationService;
                ExampleApp::PathDrawing::IPathDrawingController& m_pathDrawingController;
                
            
            public:
                DirectionReCalculationService(Eegeo::Location::ILocationService& locationService,ExampleApp::PathDrawing::IPathDrawingController& pathDrawingController);
                ~DirectionReCalculationService();
                void Update(float dt);
            };
        }
    }
}