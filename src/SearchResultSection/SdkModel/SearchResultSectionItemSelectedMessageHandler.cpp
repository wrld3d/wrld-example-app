// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultSectionItemSelectedMessageHandler.h"

#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace SdkModel
        {
            void SearchResultSectionItemSelectedMessageHandler::OnSearchResultSectionItemSelectedMessage(const SearchResultSectionItemSelectedMessage& message)
            {
                const float newDistanceFromInterest = 1000;
                if(message.InInterior())
                {
                    m_cameraTransitionController.StartTransitionTo(message.SearchResultLocationEcef(),
                                                                   InteriorsExplorer::DefaultInteriorSearchResultTransitionInterestDistance,
                                                                   message.InteriorBuildingId(),
                                                                   message.FloorIndex());
                }
                else
                {
                    m_cameraTransitionController.StartTransitionTo(message.SearchResultLocationEcef(),
                                                                   newDistanceFromInterest);
                }
                
            }

            SearchResultSectionItemSelectedMessageHandler::SearchResultSectionItemSelectedMessageHandler(
                CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                ExampleAppMessaging::TMessageBus& messageBus)
                : m_cameraTransitionController(cameraTransitionController)
                , m_messageBus(messageBus)
                , m_handleSearchResultSectionItemSelectedMessageBinding(this, &SearchResultSectionItemSelectedMessageHandler::OnSearchResultSectionItemSelectedMessage)
            {
                m_messageBus.SubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);
            }

            SearchResultSectionItemSelectedMessageHandler::~SearchResultSectionItemSelectedMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);
            }
        }
    }
}
