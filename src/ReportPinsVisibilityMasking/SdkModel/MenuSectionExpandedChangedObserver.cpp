// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuSectionExpandedChangedObserver.h"

// std library includes
#include <string>

namespace ExampleApp
{
    namespace ReportPinsVisibilityMasking
    {
        namespace SdkModel
        {
            MenuSectionExpandedChangedObserver::MenuSectionExpandedChangedObserver(ExampleAppMessaging::TMessageBus& messageBus)
            : m_messageBus(messageBus)
            , m_handler(this, &MenuSectionExpandedChangedObserver::OnMenuSectionExpandedChangedMessage)
            {
                m_messageBus.SubscribeNative(m_handler);
            }
            
            MenuSectionExpandedChangedObserver::~MenuSectionExpandedChangedObserver()
            {
                m_messageBus.UnsubscribeNative(m_handler);
            }
            
            void MenuSectionExpandedChangedObserver::InsertReportPinsExpandedChangedCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_reportPinsExpandedChangedCallbacks.AddCallback(callback);
            }
            void MenuSectionExpandedChangedObserver::RemoveReportPinsExpandedChangedCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_reportPinsExpandedChangedCallbacks.RemoveCallback(callback);
            }
            
            void MenuSectionExpandedChangedObserver::OnMenuSectionExpandedChangedMessage(const Menu::MenuSectionExpandedChangedMessage& message)
            {
                if(message.MenuSectionName() == "My Reports")
                {
                    bool expanded = message.IsExpanded();
                    m_reportPinsExpandedChangedCallbacks.ExecuteCallbacks(expanded);
                }
            }
        }
    }
}
