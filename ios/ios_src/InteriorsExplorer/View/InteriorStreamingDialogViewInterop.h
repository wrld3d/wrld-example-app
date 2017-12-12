// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInteriorStreamingDialogView.h"
#include "InteriorsExplorerViewIncludes.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class InteriorStreamingDialogViewInterop : public IInteriorStreamingDialogView
            {
            public:
                
                InteriorStreamingDialogViewInterop(InteriorStreamingDialogView* pView)
                : m_pView(pView)
                {
                }
                
                void Show();
                void Hide(bool interiorLoaded);

                
            private:
                
                InteriorStreamingDialogView* m_pView;
            };
        }
    }
}

