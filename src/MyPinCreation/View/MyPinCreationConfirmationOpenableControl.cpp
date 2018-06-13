// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationConfirmationOpenableControl.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationConfirmationOpenableControl::MyPinCreationConfirmationOpenableControl(Eegeo::Helpers::TIdentity identity)
                : OpenableControl::View::OpenableControlViewModelBase()
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity MyPinCreationConfirmationOpenableControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
