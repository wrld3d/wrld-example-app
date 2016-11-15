// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DesktopSearchMenuController.h"

#include "TagSearchRepository.h"
#include "IMenuOption.h"
#include "IModalBackgroundView.h"
#include "ISearchMenuView.h"
#include "SearchQuery.h"
#include "SearchResultViewClearedMessage.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            DesktopSearchMenuController::DesktopSearchMenuController(Menu::View::IMenuModel& model,
                                                                     Menu::View::IMenuViewModel& viewModel,
                                                                     Menu::View::IMenuView& view,
                                                                     ISearchMenuView& searchMenuView,
                                                                     Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                                                                     TagSearch::View::ITagSearchRepository& tagSearchRepository,
                                                                     Modality::View::IModalBackgroundView& modalBackgroundView,
                                                                     Modality::View::IModalityController& modalityController,
                                                                     ExampleAppMessaging::TMessageBus& messageBus,
                                                                     Reaction::View::IReactionModel& reactionModel) :
                SearchMenuController(model,
                                     viewModel,
                                     view,
                                     searchMenuView,
                                     searchSectionViewModel,
                                     tagSearchRepository,
                                     modalBackgroundView,
                                     messageBus),
                //m_modalityController(modalityController),
                m_messageBus(messageBus),
                //m_reactionModel(reactionModel),
                m_poiClosedHandler(this, &DesktopSearchMenuController::OnSearchResultPoiViewClosedMessage),
                m_poiOpenedHandler(this, &DesktopSearchMenuController::OnSearchResultPoiViewOpenedMessage)
            {
                m_menuIdentity = viewModel.GetIdentity();
                
                m_messageBus.SubscribeNative(m_poiClosedHandler);
                m_messageBus.SubscribeNative(m_poiOpenedHandler);
            }

            DesktopSearchMenuController::~DesktopSearchMenuController()
            {
                m_messageBus.UnsubscribeNative(m_poiOpenedHandler);
                m_messageBus.UnsubscribeNative(m_poiClosedHandler);
            }
            
            void DesktopSearchMenuController::OnSearchResultPoiViewOpenedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewOpenedMessage& message)
            {
            }

            void DesktopSearchMenuController::OnSearchResultPoiViewClosedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewClosedMessage& message)
            {
            }
        }
    }
}