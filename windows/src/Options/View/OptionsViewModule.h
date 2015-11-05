// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WindowsNativeState.h"
#include "Types.h"
#include "Options.h"
#include "OptionsViewIncludes.h"
#include "IOptionsViewModule.h"
#include "BidirectionalBus.h"
#include "ClearCacheMessageHandler.h"
#include "WindowsHttpCache.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            class OptionsViewModule: public IOptionsViewModule, private Eegeo::NonCopyable
            {
            private:
                OptionsView* m_pView;
                OptionsController* m_pController;
                SdkModel::ClearCacheMessageHandler* m_pClearCacheMessageHandler;

            public:
                OptionsViewModule(
                    WindowsNativeState& nativeState,
                    IOptionsViewModel& optionsViewModel,
                    Eegeo::Windows::Cache::WindowsHttpCache& httpCache,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~OptionsViewModule();

                OptionsController& GetOptionsController() const;
                OptionsView& GetOptionsView() const;
            };
        }
    }
}
