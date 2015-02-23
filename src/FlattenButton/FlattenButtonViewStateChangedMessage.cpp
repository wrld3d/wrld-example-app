// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonViewStateChangedMessage.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        FlattenButtonViewStateChangedMessage::FlattenButtonViewStateChangedMessage(bool isFlattened)
            : m_isFlattened(isFlattened)
        {

        }

        bool FlattenButtonViewStateChangedMessage::IsFlattened() const
        {
            return m_isFlattened;
        }
    }
}
