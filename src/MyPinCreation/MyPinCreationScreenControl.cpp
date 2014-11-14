// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationScreenControl.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        MyPinCreationScreenControl::MyPinCreationScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity)
        : ScreenControlViewModel::ScreenControlViewModelBase(initiallyOnScreen)
        , m_identity(identity)
        {
        }
        
        Eegeo::Helpers::TIdentity MyPinCreationScreenControl::GetIdentity() const
        {
            return m_identity;
        }
    }
}
