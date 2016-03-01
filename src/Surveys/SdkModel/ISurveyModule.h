// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Surveys.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace SdkModel
        {
            class ISurveyModule
            {
            public:
                virtual ~ISurveyModule() { }
                
                virtual SurveyObserver& GetSurveyObserver() const = 0;
            };
        }
    }
}
