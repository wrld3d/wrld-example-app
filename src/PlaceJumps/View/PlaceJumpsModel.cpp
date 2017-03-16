// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PlaceJumpsModel.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace View
        {
            PlaceJumpModel::PlaceJumpModel(const std::string& name,
                                           Eegeo::Space::LatLong location,
                                           float headingDegrees,
                                           float distance,
                                           const std::string& icon)
                : m_name(name)
                , m_location(location)
                , m_headingDegrees(headingDegrees)
                , m_distance(distance)
                , m_icon(icon)
            {

            }
        }
    }
}
