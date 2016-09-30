// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "DirectionsMenuStage.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        class DirectionsMenuItemHighlightMessage
        {
        public:
            DirectionsMenuItemHighlightMessage(int stage);

            const int GetSelectedItemIndex() const;

        private:
            int m_selectedIndex;
        };
    }
}
