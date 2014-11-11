// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "CompassViewModule.h"
#include "RenderContext.h"
#include "CompassView.h"

namespace ExampleApp
{
    namespace Compass
    {
        CompassViewModule::CompassViewModule(ICompassViewModel& viewModel,
                                             const Eegeo::Rendering::ScreenProperties& screenProperties,
                                             ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                             ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
        {
            m_pController = [[CompassViewController alloc] initWithParams:&viewModel
                                                                         :&screenProperties
                                                                         :&uiToNativeMessageBus
                                                                         :&nativeToUiMessageBus];
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
