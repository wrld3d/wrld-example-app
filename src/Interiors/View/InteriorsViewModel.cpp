// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsViewModel.h"

namespace ExampleApp
{
    namespace Interiors
    {
        namespace View
        {
            InteriorsViewModel::InteriorsViewModel(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity)
            : ScreenControl::View::ScreenControlViewModelBase(initiallyOnScreen)
            , m_identity(identity)
            {
                
            }

            Eegeo::Helpers::TIdentity InteriorsViewModel::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}