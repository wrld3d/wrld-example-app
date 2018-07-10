// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInteriorStreamingDialogView.h"
#include "InteriorsExplorerViewIncludes.h"
#include "AndroidNativeState.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class InteriorStreamingDialogView : public IInteriorStreamingDialogView
            {
            public:
                InteriorStreamingDialogView(AndroidNativeState& nativeState);

                ~InteriorStreamingDialogView();

                void Show();
                void Hide(bool interiorLoaded);

            private:
                AndroidNativeState& m_nativeState;
                jclass m_uiViewClass;
                jobject m_uiView;
            };

        }

    }
}