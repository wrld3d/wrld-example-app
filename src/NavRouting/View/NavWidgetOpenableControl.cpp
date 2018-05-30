// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetOpenableControl.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            NavWidgetOpenableControl::NavWidgetOpenableControl(Eegeo::Helpers::TIdentity identity)
                    : OpenableControl::View::OpenableControlViewModelBase()
                    , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity NavWidgetOpenableControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
