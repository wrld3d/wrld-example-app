// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "iOSAbstractionIoCModule.h"
#include "iOSInputBoxFactory.h"
#include "iOSKeyboardInputFactory.h"
#include "iOSAlertBoxFactory.h"
#include "NativeUIFactories.h"
#include "iOSPlatformAbstractionModule.h"
#include "ApplicationConfiguration.h"
#include "ImageStore.h"
#include "IHttpCache.h"

namespace ExampleApp
{
    namespace iOS
    {
        void iOSAbstractionIoCModule::Register(const TContainerBuilder& builder)
        {
            builder->registerType<Eegeo::UI::NativeInput::iOS::iOSInputBoxFactory>().as<Eegeo::UI::NativeInput::IInputBoxFactory>().singleInstance();
            builder->registerType<Eegeo::UI::NativeInput::iOS::iOSKeyboardInputFactory>().as<Eegeo::UI::NativeInput::IKeyboardInputFactory>().singleInstance();
            builder->registerType<Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory>().as<Eegeo::UI::NativeAlerts::IAlertBoxFactory>().singleInstance();
            
            builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
                                             {
                                                 return std::make_shared<Eegeo::UI::NativeUIFactories>(*(context.resolve<Eegeo::UI::NativeAlerts::IAlertBoxFactory>()),
                                                                                                       *(context.resolve<Eegeo::UI::NativeInput::IInputBoxFactory>()),
                                                                                                       *(context.resolve<Eegeo::UI::NativeInput::IKeyboardInputFactory>()));
                                             }).singleInstance();
            
            builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
                                             {
                                                 auto appConfig = context.resolve<ExampleApp::ApplicationConfig::ApplicationConfiguration>();
                                                 return std::make_shared<Eegeo::iOS::iOSPlatformAbstractionModule>(*(context.resolve<Eegeo::Helpers::Jpeg::IJpegLoader>()), appConfig->EegeoApiKey());
                                             }).as<Eegeo::Modules::IPlatformAbstractionModule>().singleInstance();
            
            builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
                                             {
                                                 return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::Modules::IPlatformAbstractionModule>()->GetTextureFileLoader());
                                             }).singleInstance();
            
            builder->registerInstanceFactory([&](Hypodermic::ComponentContext& context)
                                             {
                                                 return Hypodermic::makeExternallyOwned(context.resolve<Eegeo::Modules::IPlatformAbstractionModule>()->GetHttpCache());
                                             }).singleInstance();
            builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                             {
                                                 auto store = [[ImageStore alloc]init];
                                                 return std::make_shared<ImageStoreWrapper>(store);
                                             }).singleInstance();
        }
    }
}


