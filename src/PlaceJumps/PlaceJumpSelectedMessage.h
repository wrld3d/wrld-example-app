// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "PlaceJumpsModel.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        class PlaceJumpSelectedMessage
        {
            View::PlaceJumpModel m_placeJumpModel;

        public:
            PlaceJumpSelectedMessage(const View::PlaceJumpModel& placeJumpModel);

            const View::PlaceJumpModel& Model() const;
        };
    }
}
