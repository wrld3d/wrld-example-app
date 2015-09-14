// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerViewModel.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            InteriorsExplorerViewModel::InteriorsExplorerViewModel(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity)
            : ScreenControl::View::ScreenControlViewModelBase(initiallyOnScreen)
            , m_identity(identity)
            {
                
            }

            Eegeo::Helpers::TIdentity InteriorsExplorerViewModel::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}