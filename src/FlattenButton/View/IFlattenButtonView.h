// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlView.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            class IFlattenButtonView : public ScreenControl::View::IScreenControlView
            {
            public:
                virtual ~IFlattenButtonView() { };

                virtual void SetToggled(bool toggled) = 0;
                virtual void InsertToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback) = 0;
                virtual void RemoveToggleCallback(Eegeo::Helpers::ICallback1<bool>& callback) = 0;
                
                virtual void SetViewEnabled(bool enabled) = 0;
            };
        }
    }
}
