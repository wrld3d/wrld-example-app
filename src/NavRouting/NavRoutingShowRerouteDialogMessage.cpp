// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingShowRerouteDialogMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingShowRerouteDialogMessage::NavRoutingShowRerouteDialogMessage(const std::string& message)
        : m_message(message)
        {

        }

        const std::string& NavRoutingShowRerouteDialogMessage::GetMessage() const
        {
            return m_message;
        }
    }
}
