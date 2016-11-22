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
                const std::shared_ptr<Modality::View::IModalityController> m_modalityController;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TIdentity m_menuIdentity;
                const std::shared_ptr<Reaction::View::IReactionModel> m_reactionModel;
                
                Eegeo::Helpers::TCallback1<DesktopSearchMenuController, const ExampleApp::SearchResultPoi::SearchResultPoiViewOpenedMessage&> m_poiOpenedHandler;
                Eegeo::Helpers::TCallback1<DesktopSearchMenuController, const ExampleApp::SearchResultPoi::SearchResultPoiViewClosedMessage&> m_poiClosedHandler;

                void OnSearchResultPoiViewOpenedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewOpenedMessage& message);
                void OnSearchResultPoiViewClosedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewClosedMessage& message);

            public:
                DesktopSearchMenuController(const std::shared_ptr<Menu::View::IMenuModel>& model,
                    const std::shared_ptr<Menu::View::IMenuViewModel>& viewModel,
                    const std::shared_ptr<Menu::View::IMenuView>& view,
                    const std::shared_ptr<ISearchMenuView>& searchMenuView,
                    const std::shared_ptr<Menu::View::IMenuSectionViewModel>& searchSectionViewModel,
                    const std::shared_ptr<TagSearch::View::ITagSearchRepository>& tagSearchRepository,
                    const std::shared_ptr<Modality::View::IModalBackgroundView>& modalBackgroundView,
                    const std::shared_ptr<Modality::View::IModalityController>& modalityController,
                    const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                    const std::shared_ptr<Reaction::View::IReactionModel>& reactionModel);

                ~DesktopSearchMenuController();
            };
        }
    }
}