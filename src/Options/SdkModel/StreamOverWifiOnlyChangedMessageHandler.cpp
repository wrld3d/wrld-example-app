// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "StreamOverWifiOnlyChangedMessageHandler.h"
#include "INetworkCapabilities.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            StreamOverWifiOnlyChangedMessageHandler::StreamOverWifiOnlyChangedMessageHandler(ExampleAppMessaging::TMessageBus& messageBus,
                                                                                             Net::SdkModel::INetworkCapabilities& networkCapabilities)
            : m_messageBus(messageBus)
            , m_messageHandlerBinding(this, &StreamOverWifiOnlyChangedMessageHandler::OnPerformedStreamOverWifiOnlyChange)
            , m_networkCapabilities(networkCapabilities)
            {
                m_messageBus.SubscribeNative(m_messageHandlerBinding);
            }
            
            StreamOverWifiOnlyChangedMessageHandler::~StreamOverWifiOnlyChangedMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_messageHandlerBinding);
            }
            
            void StreamOverWifiOnlyChangedMessageHandler::OnPerformedStreamOverWifiOnlyChange(const StreamOverWifiOnlyChangedMessage& message)
            {
                // We do not expect this value to change other than via the dispatch of this message, so should always toggle.
                // If these semantics change this assert should be removed.
                Eegeo_ASSERT(message.StreamOverWifiOnly() != m_networkCapabilities.StreamOverWifiOnly());
                
                m_networkCapabilities.SetStreamOverWifiOnlyMode(message.StreamOverWifiOnly());
            }
        }
    }
}
