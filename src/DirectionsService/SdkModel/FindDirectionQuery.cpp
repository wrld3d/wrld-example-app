// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FindDirectionQuery.h"


namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            
            FindDirectionQuery::FindDirectionQuery(const Eegeo::Space::LatLongAltitude& startLocation,const Eegeo::Space::LatLongAltitude& endLocation,bool isInterior)
            : m_startLocation(startLocation)
            , m_endLocation(endLocation)
            , m_isInterior(isInterior)
            {
            
            }
            
            FindDirectionQuery::~FindDirectionQuery()
            {
            
            }
            
            bool FindDirectionQuery::IsInterior() const
            {
                return m_isInterior;
            }
            
            const Eegeo::Space::LatLongAltitude& FindDirectionQuery::StartLocation() const
            {
                return m_startLocation;
            }
            
            const Eegeo::Space::LatLongAltitude& FindDirectionQuery::EndLocation() const
            {
                return m_endLocation;
            }


            
            

        }
    }
}





