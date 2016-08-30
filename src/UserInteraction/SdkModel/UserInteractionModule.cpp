// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "UserInteractionModule.h"

#include "UserInteractionController.h"
#include "UserInteractionEnabledObserver.h"
#include "UserInteractionModel.h"

namespace ExampleApp
{
    namespace UserInteraction
    {
        namespace SdkModel
        {
            void UserInteractionModule::Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            {
                builder->registerType<UserInteractionModel>().singleInstance();
                
            }
        }
    }
}