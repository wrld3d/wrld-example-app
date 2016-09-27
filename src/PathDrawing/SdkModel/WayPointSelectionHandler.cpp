// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WayPointSelectionHandler.h"
#include "DirectionsMenuStateChangedMessage.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {
            WayPointSelectionHandler::WayPointSelectionHandler(ExampleAppMessaging::TMessageBus& messageBus)
            : m_messageBus(messageBus)
            {
            
            }
            
            WayPointSelectionHandler::~WayPointSelectionHandler()
            {
            
            }
            
            void WayPointSelectionHandler::SelectPin()
            {
                //TODO Open menu if closed and highlight way point in menu
                DirectionsMenuInitiation::DirectionsMenuStateChangedMessage message(ExampleApp::DirectionsMenuInitiation::Active);
                m_messageBus.Publish(message);
            }
        }
    }
}
