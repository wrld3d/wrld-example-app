// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "VirtualKeyboardStateChangedMessage.h"

namespace ExampleApp
{
    namespace VirtualKeyboard
    {
        VirtualKeyboardStateChangedMessage::VirtualKeyboardStateChangedMessage(const bool isVisible)
            : m_isVisible(isVisible)
        {
        }

        const bool VirtualKeyboardStateChangedMessage::IsVirtualKeyboardVisible() const
        {
            return m_isVisible;
        }
    }
}
