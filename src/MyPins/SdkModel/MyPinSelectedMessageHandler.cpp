// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinSelectedMessageHandler.h"
#include "ICameraTransitionController.h"
#include "InteriorId.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            MyPinSelectedMessageHandler::MyPinSelectedMessageHandler(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
            		ExampleAppMessaging::TMessageBus& messageBus,
					ExampleApp::WifiInfo::IRestrictedBuildingService& restrictedBuildingInformationService)
                : m_cameraTransitionController(cameraTransitionController)
                , m_messageBus(messageBus)
                , m_handlerBinding(this, &MyPinSelectedMessageHandler::OnMyPinSelectedMessage)
                , m_restrictedBuildingInformationService(restrictedBuildingInformationService)
            {
                m_messageBus.SubscribeNative(m_handlerBinding);
            }

            MyPinSelectedMessageHandler::~MyPinSelectedMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handlerBinding);
            }

            void MyPinSelectedMessageHandler::OnMyPinSelectedMessage(const MyPinSelectedMessage& message)
            {
                const float MyPinAltitude = 1500.0f;
                if(message.GetInteriorId() == Eegeo::Resources::Interiors::InteriorId::NullId())
                {
                    m_cameraTransitionController.StartTransitionTo(message.GetPinLocation().ToECEF(),
                                                                  MyPinAltitude);
                }
                else
                {
                	if(!m_restrictedBuildingInformationService.CanAccessBuildingWithCurrentNetwork(message.GetInteriorId().Value()))
                	 {
                		m_restrictedBuildingInformationService.ShowAlertMessage();
                	 }
                	 else
                	 {
                		 m_cameraTransitionController.StartTransitionTo(message.GetPinLocation().ToECEF(),
                                                               InteriorsExplorer::DefaultInteriorSearchResultTransitionInterestDistance,
                                                               message.GetInteriorId(),
                                                               message.GetFloorIndex());
                	 }
                }
            }
        }
    }
}
