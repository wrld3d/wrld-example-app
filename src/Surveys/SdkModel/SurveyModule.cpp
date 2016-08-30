// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SurveyModule.h"

#include "SurveyObserver.h"
#include "IPersistentSettingsModel.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace SdkModel
        {
            void SurveyModule::Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            {
                builder->registerType<SurveyObserver>().singleInstance();
            }
        }
    }
}
