// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchMenuController.h"

#include "TagSearch.h"
#include "Modality.h"
#include "SearchMenu.h"
#include "IModalityController.h"
#include "IReactionModel.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class DesktopSearchMenuController : public SearchMenuController
            {
                //Modality::View::IModalityController& m_modalityController;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TIdentity m_menuIdentity;
                //Reaction::View::IReactionModel& m_reactionModel;
                
                Eegeo::Helpers::TCallback1<DesktopSearchMenuController, const ExampleApp::SearchResultPoi::SearchResultPoiViewOpenedMessage&> m_poiOpenedHandler;
                Eegeo::Helpers::TCallback1<DesktopSearchMenuController, const ExampleApp::SearchResultPoi::SearchResultPoiViewClosedMessage&> m_poiClosedHandler;

                void OnSearchResultPoiViewOpenedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewOpenedMessage& message);
                void OnSearchResultPoiViewClosedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewClosedMessage& message);

            public:
                DesktopSearchMenuController(Menu::View::IMenuModel& model,
                    Menu::View::IMenuViewModel& viewModel,
                    Menu::View::IMenuView& view,
                    ISearchMenuView& searchMenuView,
                    Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                    TagSearch::View::ITagSearchRepository& tagSearchRepository,
                    Modality::View::IModalBackgroundView& modalBackgroundView,
                    Modality::View::IModalityController& modalityController,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Reaction::View::IReactionModel& reactionModel);

                ~DesktopSearchMenuController();
            };
        }
    }
}