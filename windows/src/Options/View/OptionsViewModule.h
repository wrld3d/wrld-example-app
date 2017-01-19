// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WindowsNativeState.h"
#include "Types.h"
#include "Options.h"
#include "OptionsViewIncludes.h"
#include "IOptionsViewModule.h"
#include "BidirectionalBus.h"
#include "ClearCacheMessageHandler.h"
#include "Helpers.h"

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
                    Eegeo::Helpers::IHttpCache& httpCache,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    bool isInKioskMode
                );

                ~OptionsViewModule();

                OptionsController& GetOptionsController() const;
                OptionsView& GetOptionsView() const;
            };
        }
    }
}
