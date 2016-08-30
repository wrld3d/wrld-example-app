// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsModule.h"
#include "MyPinCreationDetailsViewModel.h"
#include "IReactionControllerModel.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            MyPinCreationDetailsModule::MyPinCreationDetailsModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            : m_builder(builder)
            {
            }
            
            void MyPinCreationDetailsModule::Register()
            {
                m_builder->registerType<MyPinCreationDetailsViewModel>().as<IMyPinCreationDetailsViewModel>().singleInstance();
            }
        }
    }
}
