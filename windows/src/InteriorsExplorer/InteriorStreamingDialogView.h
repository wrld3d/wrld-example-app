// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInteriorStreamingDialogView.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class InteriorStreamingDialogView : public IInteriorStreamingDialogView
            {
            private:
                WindowsNativeState& m_nativeState;

                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;

                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<void> mOpenInteriorStreamingDialogView;
                Helpers::ReflectionHelpers::Method<void> mDismissInteriorStreamingDialogView;
                Helpers::ReflectionHelpers::Method<void> mCancelInteriorStreamingDialogView;


            public:

                InteriorStreamingDialogView();

                void Show();
                void Hide(bool interiorLoaded);
            };
        }
    }
}