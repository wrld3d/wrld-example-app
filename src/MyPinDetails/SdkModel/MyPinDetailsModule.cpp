// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsModule.h"
#include "MyPinDetailsViewModel.h"
#include "MyPinDetailsDisplayService.h"
#include "MyPinDetailsViewRemovePinHandler.h"
#include "MyPinDetailsModelSelectedObserver.h"
#include "IReactionControllerModel.h"
#include "ISearchResultPoiViewModel.h"
#include "IMyPinsService.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace SdkModel
        {
            MyPinDetailsModule::MyPinDetailsModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            : m_builder(builder)
            {
            }
            
            void MyPinDetailsModule::Register()
            {
                m_builder->registerType<View::MyPinDetailsViewModel>().as<View::IMyPinDetailsViewModel>().singleInstance();
                m_builder->registerType<View::MyPinDetailsDisplayService>().as<View::IMyPinDetailsDisplayService>().singleInstance();
                m_builder->registerType<View::MyPinDetailsModelSelectedObserver>().singleInstance();
                m_builder->registerType<MyPinDetailsViewRemovePinHandler>().singleInstance();
            }
        }
    }
}
