// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Options.h"
#include "IOptionsViewModule.h"
#include "BidirectionalBus.h"
#include "ClearCacheMessageHandler.h"
#include "iOSHttpCache.h"
#include "Tasks.h"

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
                OptionsViewModule(IOptionsViewModel& viewModel,
                                  iOSHttpCache& httpCache,
                                  ExampleAppMessaging::TMessageBus& messageBus,
                                  Eegeo::Concurrency::Tasks::IWorkPool& workPool);

                ~OptionsViewModule();

                OptionsController& GetOptionsController() const;

                OptionsView& GetOptionsView() const;
            };
        }
    }
}
