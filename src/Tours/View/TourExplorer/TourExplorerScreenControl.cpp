// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourExplorerScreenControl.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                TourExplorerScreenControl::TourExplorerScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity)
                : ScreenControl::View::ScreenControlViewModelBase(initiallyOnScreen)
                , m_identity(identity)
                {
                }
                
                Eegeo::Helpers::TIdentity TourExplorerScreenControl::GetIdentity() const
                {
                    return m_identity;
                }
            }
        }
    }
}
