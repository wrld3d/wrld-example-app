// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorStreamingDialogViewInterop.h"
#include "InteriorStreamingDialogView.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            void InteriorStreamingDialogViewInterop::Show()
            {
                [m_pView show];
            }
            
            void InteriorStreamingDialogViewInterop::Hide(bool interiorLoaded)
            {
                [m_pView hide];
            }
        }
    }
}
