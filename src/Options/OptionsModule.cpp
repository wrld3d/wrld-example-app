// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsModule.h"
#include "OptionsViewModel.h"
#include "StreamOverWifiOnlyChangedMessageHandler.h"
#include "CacheEnabledChangedMessageHandler.h"
#include "CompletedCacheClearMessageHandler.h"
#include "INetworkCapabilities.h"
#include "IReactionControllerModel.h"

namespace ExampleApp
{
    namespace Options
    {
        void OptionsModule::Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
        {
            builder->registerType<View::OptionsViewModel>().as<View::IOptionsViewModel>().singleInstance();
            builder->registerType<SdkModel::StreamOverWifiOnlyChangedMessageHandler>().singleInstance();
            builder->registerType<SdkModel::CacheEnabledChangedMessageHandler>().singleInstance();
            builder->registerType<View::CompletedCacheClearMessageHandler>().singleInstance();
        }
    }
}
