// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include <string>

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            class IInitialExperienceIntroView
            {
            public:
                virtual ~IInitialExperienceIntroView() {}
                
                virtual void Show() = 0;
                virtual void Dismiss() = 0;
                
                virtual void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void ShowExitIUX() = 0;
                virtual void DismissExitIUX() = 0;

            };
        }
    }
}