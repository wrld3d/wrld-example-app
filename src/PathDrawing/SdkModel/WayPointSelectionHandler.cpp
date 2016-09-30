// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WayPointSelectionHandler.h"
#include "DirectionsMenuItemHighlightMessage.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {
            WayPointSelectionHandler::WayPointSelectionHandler(WayPointModel& wayPointModel,ExampleAppMessaging::TMessageBus& messageBus)
            :m_wayPointModel(wayPointModel)
            ,m_messageBus(messageBus)
            
            {
            
            }
            
            WayPointSelectionHandler::~WayPointSelectionHandler()
            {
            
            }
            
            void WayPointSelectionHandler::SelectPin()
            {
                DirectionsMenuInitiation::DirectionsMenuItemHighlightMessage message(m_wayPointModel.GetWpId());
                m_messageBus.Publish(message);
            }
        }
    }
}
