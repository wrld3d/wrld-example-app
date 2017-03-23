// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace SearchMenu
    {
        class OpenSearchMenuMessage
        {
            bool m_openState;

        public:
            OpenSearchMenuMessage(bool openMenu);
            bool OpenMenu() const;
        };
    }
}
