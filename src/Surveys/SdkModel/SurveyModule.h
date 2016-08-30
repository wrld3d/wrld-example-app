// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Hypodermic/ContainerBuilder.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace SdkModel
        {
            class SurveyModule
            {
            public:
                void Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder);
            };
        }
    }
}
