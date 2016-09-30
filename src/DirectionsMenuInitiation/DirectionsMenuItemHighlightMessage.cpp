// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuItemHighlightMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        DirectionsMenuItemHighlightMessage::DirectionsMenuItemHighlightMessage(int stage):
        m_selectedIndex(stage)
        {

        }

        const int DirectionsMenuItemHighlightMessage::GetSelectedItemIndex()  const  {
            
            return m_selectedIndex;
        }
    }
}
