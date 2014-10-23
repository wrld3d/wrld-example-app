// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "CompassViewModule.h"
#include "RenderContext.h"
#include "CompassView.h"

namespace ExampleApp
{
    namespace Compass
    {
        CompassViewModule::CompassViewModule(ICompassModel& model,
                                             ICompassViewModel& viewModel,
                                             const Eegeo::Rendering::ScreenProperties& screenProperties)
        {
            m_pController = [[CompassViewController alloc] initWithParams:&model
                                                                         :&viewModel
                                                                         :&screenProperties];
        }
        
        CompassViewModule::~CompassViewModule()
        {
            [m_pController release];
        }
        
        CompassViewController& CompassViewModule::GetCompassViewController() const
        {
            return *m_pController;
        }
        
        CompassView& CompassViewModule::GetCompassView() const
        {
            return *[m_pController pCompassView];
        }
    }
}
