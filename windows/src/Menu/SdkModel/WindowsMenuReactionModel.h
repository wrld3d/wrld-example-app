// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IMenuReactionModel.h"
#include "BidirectionalBus.h"
#include "SearchResultPoiViewOpenedMessage.h"
#include "SearchResultPoiViewClosedMessage.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class WindowsMenuReactionModel : public Menu::View::IMenuReactionModel
            {
                bool m_shouldCloseMenu;
                bool m_shouldOpenMenu;

                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<WindowsMenuReactionModel, const ExampleApp::SearchResultPoi::SearchResultPoiViewOpenedMessage&> m_poiOpenedHandler;
                Eegeo::Helpers::TCallback1<WindowsMenuReactionModel, const ExampleApp::SearchResultPoi::SearchResultPoiViewClosedMessage&> m_poiClosedHandler;

                void OnSearchResultPoiViewOpenedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewOpenedMessage& message);
                void OnSearchResultPoiViewClosedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewClosedMessage& message);

            public:
                WindowsMenuReactionModel(bool menuClose,
                                         bool menuOpen,
                                         ExampleAppMessaging::TMessageBus& mmessageBus);

                ~WindowsMenuReactionModel();

                bool GetShouldCloseMenu() const;

                bool GetShouldOpenMenu() const;
            };
        }
    }
}
