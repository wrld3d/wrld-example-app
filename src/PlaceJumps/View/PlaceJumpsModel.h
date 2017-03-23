// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IPlaceJumpsModel.h"
#include "Types.h"
#include "LatLongAltitude.h"
#include <string>
#include <vector>

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace View
        {
            class PlaceJumpModel : public IPlaceJumpModel
            {
            public:

                PlaceJumpModel(const std::string& name, Eegeo::Space::LatLong location, float headingDegrees, float distance, const std::string& icon);

                std::string GetName() const
                {
                    return m_name;
                }
                Eegeo::Space::LatLong GetLocation() const
                {
                    return m_location;
                }
                float GetHeadingDegrees() const
                {
                    return m_headingDegrees;
                }
                float GetDistance() const
                {
                    return m_distance;
                }
                const std::string& GetIcon() const
                {
                    return m_icon;
                }

            private:

                std::string m_name;
                Eegeo::Space::LatLong m_location;
                float m_headingDegrees;
                float m_distance;
                std::string m_icon;

            };
        }

    }
}
