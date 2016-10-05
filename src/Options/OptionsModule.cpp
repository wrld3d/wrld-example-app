// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsModule.h"
#include "OptionsViewModel.h"
#include "StreamOverWifiOnlyChangedMessageHandler.h"
#include "CacheEnabledChangedMessageHandler.h"
#include "CompletedCacheClearMessageHandler.h"
#include "INetworkCapabilities.h"
#include "IReactionControllerModel.h"
#include "ClearCacheMessageHandler.h"
#include "OptionsController.h"
#include "ClearCacheMessageHandler.h"
#include "IWorkPool.h"
#include "IOptionsView.h"

namespace ExampleApp
{
    namespace Options
    {
        void OptionsModule::Register(const TContainerBuilder& builder)
        {
            builder->registerType<View::OptionsViewModel>().as<View::IOptionsViewModel>().singleInstance();
            builder->registerType<SdkModel::StreamOverWifiOnlyChangedMessageHandler>().singleInstance();
            builder->registerType<SdkModel::CacheEnabledChangedMessageHandler>().singleInstance();
            builder->registerType<View::CompletedCacheClearMessageHandler>().singleInstance();
            builder->registerType<View::OptionsController>().singleInstance();
            builder->registerType<SdkModel::ClearCacheMessageHandler>().singleInstance();
        }
        
        void OptionsModule::RegisterNativeLeaves()
        {
            RegisterLeaf<SdkModel::ClearCacheMessageHandler>();
            RegisterLeaf<SdkModel::CacheEnabledChangedMessageHandler>();
            RegisterLeaf<SdkModel::StreamOverWifiOnlyChangedMessageHandler>();
        }
        
        void OptionsModule::RegisterUiLeaves()
        {
            RegisterLeaf<View::OptionsController>();
            RegisterLeaf<View::CompletedCacheClearMessageHandler>();
        }
        
        void OptionsModule::RegisterOpenablesAndReactors()
        {
            RegisterOpenable(&Resolve<View::IOptionsViewModel>()->GetOpenableControl());
        }
    }
}
