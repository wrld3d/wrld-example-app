// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Options.h"
#include "IOptionsModule.h"
#include "OptionsViewModel.h"
#include "IIdentity.h"
#include "Reaction.h"
#include "OptionsSdkIncludes.h"
#include "BidirectionalBus.h"
#include "IHttpCache.h"
#include "NetIncludes.h"
#include "CompletedCacheClearMessageHandler.h"

namespace ExampleApp
{
    namespace Options
    {
        class OptionsModule : public IOptionsModule, private Eegeo::NonCopyable
        {
            View::OptionsViewModel* m_pOptionsViewModel;
            SdkModel::StreamOverWifiOnlyChangedMessageHandler* m_pStreamOverWifiOnlyChangedMessageHandler;
            SdkModel::CacheEnabledChangedMessageHandler* m_pCacheEnabledChangedMessageHandler;
            View::CompletedCacheClearMessageHandler* m_pCompletedCacheClearMessageHandler;
            
        public:
            OptionsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                          Reaction::View::IReactionControllerModel& reactionControllerModel,
                          ExampleAppMessaging::TMessageBus& messageBus,
                          Net::SdkModel::INetworkCapabilities& networkCapabilities);
            
            ~OptionsModule();
            
            View::IOptionsViewModel& GetOptionsViewModel() const;
            
            OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const;
        };
    }
}
