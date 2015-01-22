// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PlaceJumpSelectedMessage.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        PlaceJumpSelectedMessage::PlaceJumpSelectedMessage(const View::PlaceJumpModel& placeJumpModel)
            : m_placeJumpModel(placeJumpModel)
        {
        }

        const View::PlaceJumpModel& PlaceJumpSelectedMessage::Model() const
        {
            return m_placeJumpModel;
        }
    }
}
