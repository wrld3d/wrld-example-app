// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ActiveTourQuitSelectedMessage.h"

namespace ExampleApp
{
    namespace Tours
    {
        ActiveTourQuitSelectedMessage::ActiveTourQuitSelectedMessage(bool exitTours)
        : m_exitTours(exitTours)
        {
        }
        
        bool ActiveTourQuitSelectedMessage::ExitTours() const
        {
            return m_exitTours;
        }
    }
}
