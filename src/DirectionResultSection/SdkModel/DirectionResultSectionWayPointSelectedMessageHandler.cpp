// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionResultSectionWayPointSelectedMessageHandler.h"

namespace ExampleApp
{
    namespace DirectionResultSection
    {
        namespace SdkModel
        {

            
            DirectionResultSectionWayPointSelectedMessageHandler::DirectionResultSectionWayPointSelectedMessageHandler(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,ExampleAppMessaging::TMessageBus& messageBus)
            : m_cameraTransitionController(cameraTransitionController)
            , m_messageBus(messageBus)
            , m_handleDirectionResultSectionItemSelectedMessageBinding(this, &DirectionResultSectionWayPointSelectedMessageHandler::OnSearchResultSectionItemSelectedMessage)
            {

                m_cameraTransitionController.IsTransitioning();
                
                m_messageBus.SubscribeNative(m_handleDirectionResultSectionItemSelectedMessageBinding);

            }
            DirectionResultSectionWayPointSelectedMessageHandler::~DirectionResultSectionWayPointSelectedMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handleDirectionResultSectionItemSelectedMessageBinding);
            }
            void DirectionResultSectionWayPointSelectedMessageHandler::OnSearchResultSectionItemSelectedMessage(const DirectionResultSection::DirectionResultSectionItemSelectedMessage& message)
            {
            
            
            }
            

        }
    }
}