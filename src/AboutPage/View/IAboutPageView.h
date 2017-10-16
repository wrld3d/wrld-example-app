// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include <string>

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            class IAboutPageView
            {
            public:
                virtual ~IAboutPageView() { };
                virtual void Open() = 0;
                virtual void Close() = 0;
                virtual void SetContent(const std::string& content) = 0;

                virtual void InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void InsertLogoLongPressCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveLogoLongPressCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
