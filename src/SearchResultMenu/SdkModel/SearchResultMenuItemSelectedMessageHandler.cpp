// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuItemSelectedMessageHandler.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace SdkModel
        {
            void SearchResultMenuItemSelectedMessageHandler::OnSearchResultMenuItemSelectedMessage(const SearchResultMenuItemSelectedMessage& message)
            {
                const float newDistanceFromInterest = 1000;
                const float newInteriorDistanceFromInterest = 300;
                if(message.InInterior())
                {
                    m_cameraTransitionController.StartTransitionTo(message.SearchResultLocationEcef(),
                                                                   newInteriorDistanceFromInterest,
                                                                   message.InteriorBuildingId(),
                                                                   message.FloorIndex());
                }
                else
                {
                    m_cameraTransitionController.StartTransitionTo(message.SearchResultLocationEcef(),
                                                                   newDistanceFromInterest);
                }
                
            }

            SearchResultMenuItemSelectedMessageHandler::SearchResultMenuItemSelectedMessageHandler(
                CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                ExampleAppMessaging::TMessageBus& messageBus)
                : m_cameraTransitionController(cameraTransitionController)
                , m_messageBus(messageBus)
                , m_handleSearchResultMenuItemSelectedMessageBinding(this, &SearchResultMenuItemSelectedMessageHandler::OnSearchResultMenuItemSelectedMessage)
            {
                m_messageBus.SubscribeNative(m_handleSearchResultMenuItemSelectedMessageBinding);
            }

            SearchResultMenuItemSelectedMessageHandler::~SearchResultMenuItemSelectedMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handleSearchResultMenuItemSelectedMessageBinding);
            }
        }
    }
}
