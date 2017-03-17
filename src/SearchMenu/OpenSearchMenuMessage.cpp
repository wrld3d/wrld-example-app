// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "OpenSearchMenuMessage.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        OpenSearchMenuMessage::OpenSearchMenuMessage(bool openMenu)
            : m_openState(openMenu)
        {
        }

        bool OpenSearchMenuMessage::OpenMenu() const
        {
            return m_openState;
        }
    }
}
