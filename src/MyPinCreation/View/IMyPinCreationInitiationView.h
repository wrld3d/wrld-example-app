// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlView.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class IMyPinCreationInitiationView : public ScreenControl::View::IScreenControlView
            {
            public:

                virtual ~IMyPinCreationInitiationView() { }

                virtual void OnSelected() = 0;
                virtual void InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
