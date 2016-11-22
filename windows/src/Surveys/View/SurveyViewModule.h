// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Module.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace View
        {
            class SurveyViewModule : public Module
            {
            public:
                void Register(const TContainerBuilder& builder);
            };
        }
    }
}
