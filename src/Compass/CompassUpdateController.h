// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Compass.h"
#include "ICompassUpdateController.h"
#include "Location.h"
#include "CompassGpsMode.h"
#include "NavigationService.h"

namespace ExampleApp
{
    namespace Compass
    {
        class CompassUpdateController : public ICompassUpdateController, private Eegeo::NonCopyable
        {
        public:
            
            CompassUpdateController(ICompassModel& model,
                                    ICompassViewModel& viewModel,
                                    Eegeo::Location::NavigationService& navigationService);
            
            void Update(float deltaSeconds);
            
        private:
            ICompassModel& m_model;
            ICompassViewModel& m_viewModel;
            Eegeo::Location::NavigationService& m_navigationService;
                
        };
    }
}
