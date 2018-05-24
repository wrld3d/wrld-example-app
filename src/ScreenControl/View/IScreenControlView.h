// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace ScreenControl
    {
        namespace View
        {
            typedef int TScreenControlViewState;
            class IScreenControlView
            {
            public:
                virtual ~IScreenControlView() { };

                virtual void SetOnScreen() = 0;
                virtual void SetOffScreen() = 0;
            };
            class IMultiStateScreenControlView : public virtual IScreenControlView
            {
            public:
                virtual void SetState(TScreenControlViewState state) = 0;
            };
        }
    }
}
