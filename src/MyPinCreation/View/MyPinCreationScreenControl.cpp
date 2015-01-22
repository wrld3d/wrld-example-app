// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationScreenControl.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationScreenControl::MyPinCreationScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity)
                : ScreenControl::View::ScreenControlViewModelBase(initiallyOnScreen)
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity MyPinCreationScreenControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
