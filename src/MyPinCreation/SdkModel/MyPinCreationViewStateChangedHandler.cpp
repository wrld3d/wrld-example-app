// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationViewStateChangedHandler.h"
#include "ISearchRefreshService.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace SdkModel
        {
            MyPinCreationViewStateChangedHandler::MyPinCreationViewStateChangedHandler(
                                                                                       const std::shared_ptr<IMyPinCreationModel>& myPinCreationModel,
                                                                                       const std::shared_ptr<Search::SdkModel::ISearchRefreshService>& searchRefreshService,
                                                                                       const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus)
                : m_myPinCreationModel(myPinCreationModel)
                , m_searchRefreshService(searchRefreshService)
                , m_messageBus(messageBus)
                , m_handler(this, &MyPinCreationViewStateChangedHandler::OnMyPinCreationViewStateChangedMessage)
            {
                m_messageBus->SubscribeNative(m_handler);
            }

            MyPinCreationViewStateChangedHandler::~MyPinCreationViewStateChangedHandler()
            {
                m_messageBus->UnsubscribeNative(m_handler);
            }

            void MyPinCreationViewStateChangedHandler::OnMyPinCreationViewStateChangedMessage(const MyPinCreationViewStateChangedMessage& message)
            {
                m_myPinCreationModel->SetCreationStage(message.GetMyPinCreationStage());
                m_searchRefreshService->SetEnabled(message.GetMyPinCreationStage() == MyPinCreation::Inactive);
            }
        }
    }
}
