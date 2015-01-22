// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace FlattenButton
    {
        class FlattenButtonModelStateChangedMessage
        {
            bool m_isFlattened;

        public:
            FlattenButtonModelStateChangedMessage(bool isFlattened);

            bool IsFlattened() const;
        };
    }
}
