// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Menu
    {
        class MenuDragStateChangedMessage
        {
            bool m_isDragging;
            
        public:
            MenuDragStateChangedMessage(bool isDragging);
            
            bool IsDragging() const;
        };
    }
}
