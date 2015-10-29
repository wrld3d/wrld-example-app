// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

// eeGeo SDK includes
#include "BidirectionalBus.h"
#include "CallbackCollection.h"
#include "ICallback.h"
// App includes
#include "MenuSectionExpandedChangedMessage.h"

namespace ExampleApp
{
    namespace ReportPinsVisibilityMasking
    {
        namespace SdkModel
        {
            class MenuSectionExpandedChangedObserver
            {
            private:
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<MenuSectionExpandedChangedObserver, const Menu::MenuSectionExpandedChangedMessage&> m_handler;
                Eegeo::Helpers::CallbackCollection1<bool> m_reportPinsExpandedChangedCallbacks;
                
            public:
                MenuSectionExpandedChangedObserver(ExampleAppMessaging::TMessageBus& messageBus);
                
                ~MenuSectionExpandedChangedObserver();
                
                void InsertExpandedChangedCallback(Eegeo::Helpers::ICallback1<bool>& callback);
                void RemoveExpandedChangedCallback(Eegeo::Helpers::ICallback1<bool>& callback);
                
            private:
                void OnMenuSectionExpandedChangedMessage(const Menu::MenuSectionExpandedChangedMessage& message);
            };
        }
    }
}
