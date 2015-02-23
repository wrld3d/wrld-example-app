// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonModelStateChangedMessage.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        FlattenButtonModelStateChangedMessage::FlattenButtonModelStateChangedMessage(bool isFlattened)
            : m_isFlattened(isFlattened)
        {

        }

        bool FlattenButtonModelStateChangedMessage::IsFlattened() const
        {
            return m_isFlattened;
        }
    }
}
