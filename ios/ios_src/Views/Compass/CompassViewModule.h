// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "CompassViewIncludes.h"
#include "Rendering.h"
#include "Compass.h"
#include "ICompassViewModule.h"
#include "NativeToUiMessageBus.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
    namespace Compass
    {
        class CompassViewModule: public ICompassViewModule, private Eegeo::NonCopyable
        {
        private:
            CompassViewController* m_pController;
            
        public:
            CompassViewModule(ICompassViewModel& viewModel,
                              const Eegeo::Rendering::ScreenProperties& screenProperties,
                              ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                              ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);
            
            ~CompassViewModule();
            
            CompassViewController& GetCompassViewController() const;
            
            CompassView& GetCompassView() const;
        };
    }
}
