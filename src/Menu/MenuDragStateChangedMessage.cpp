// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuDragStateChangedMessage.h"

namespace ExampleApp
{
    namespace Menu
    {
        MenuDragStateChangedMessage::MenuDragStateChangedMessage(bool isDragging)
        : m_isDragging(isDragging)
        {
            
        }
            
        bool MenuDragStateChangedMessage::IsDragging() const
        {
            return m_isDragging;
        }
    }
}