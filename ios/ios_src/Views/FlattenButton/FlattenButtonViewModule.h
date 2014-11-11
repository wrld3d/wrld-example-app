// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "FlattenButtonViewIncludes.h"
#include "Rendering.h"
#include "FlattenButton.h"
#include "IFlattenButtonViewModule.h"
#include "UiToNativeMessageBus.h"
#include "NativeToUiMessageBus.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        class FlattenButtonViewModule: public IFlattenButtonViewModule, private Eegeo::NonCopyable
        {
        private:
            FlattenButtonViewController* m_pController;
            FlattenButtonView* m_pView;
            
        public:
            FlattenButtonViewModule(IFlattenButtonModel& model,
                                    IFlattenButtonViewModel& viewModel,
                                    const Eegeo::Rendering::ScreenProperties& screenProperties,
                                    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                    ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);
            
            ~FlattenButtonViewModule();
            
            FlattenButtonViewController& GetFlattenButtonViewController() const;
            
            FlattenButtonView& GetFlattenButtonView() const;
        };
    }
}
