// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace VirtualKeyboard
    {
        class VirtualKeyboardStateChangedMessage
        {
        public:
            VirtualKeyboardStateChangedMessage(const bool isVisible);
            const bool IsVirtualKeyboardVisible() const;

        private:
            const bool m_isVisible;
        };
    }
}
