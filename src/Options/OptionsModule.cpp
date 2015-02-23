// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsModule.h"
#include "OptionsViewModel.h"
#include "StreamOverWifiOnlyChangedMessageHandler.h"
#include "CacheEnabledChangedMessageHandler.h"
#include "INetworkCapabilities.h"

namespace ExampleApp
{
    namespace Options
    {
        OptionsModule::OptionsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                     Reaction::View::IReactionControllerModel& reactionControllerModel,
                                     ExampleAppMessaging::TMessageBus& messageBus,
                                     Net::SdkModel::INetworkCapabilities& networkCapabilities)
        {
            m_pOptionsViewModel = Eegeo_NEW(View::OptionsViewModel)(identityProvider.GetNextIdentity(),
                                                                    reactionControllerModel,
                                                                    networkCapabilities.StreamOverWifiOnly(),
                                                                    networkCapabilities.HttpCachingEnabled());
            
            m_pStreamOverWifiOnlyChangedMessageHandler = Eegeo_NEW(SdkModel::StreamOverWifiOnlyChangedMessageHandler)(messageBus,
                                                                                                                      networkCapabilities);
            
            m_pCacheEnabledChangedMessageHandler = Eegeo_NEW(SdkModel::CacheEnabledChangedMessageHandler)(networkCapabilities,
                                                                                                          messageBus);
            
            m_pCompletedCacheClearMessageHandler = Eegeo_NEW(View::CompletedCacheClearMessageHandler)(*m_pOptionsViewModel,
                                                                                                      messageBus);
        }
        
        OptionsModule::~OptionsModule()
        {
            Eegeo_DELETE m_pCompletedCacheClearMessageHandler;
            Eegeo_DELETE m_pCacheEnabledChangedMessageHandler;
            Eegeo_DELETE m_pStreamOverWifiOnlyChangedMessageHandler;
            Eegeo_DELETE m_pOptionsViewModel;
        }
        
        View::IOptionsViewModel& OptionsModule::GetOptionsViewModel() const
        {
            return *m_pOptionsViewModel;
        }
        
        OpenableControl::View::IOpenableControlViewModel& OptionsModule::GetObservableOpenableControl() const
        {
            return m_pOptionsViewModel->GetOpenableControl();
        }
    }
}
