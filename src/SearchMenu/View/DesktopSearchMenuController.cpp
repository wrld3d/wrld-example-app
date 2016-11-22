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
            DesktopSearchMenuController::DesktopSearchMenuController(const std::shared_ptr<Menu::View::IMenuModel>& model,
                                                                     const std::shared_ptr<Menu::View::IMenuViewModel>& viewModel,
                                                                     const std::shared_ptr<Menu::View::IMenuView>& view,
                                                                     const std::shared_ptr<ISearchMenuView>& searchMenuView,
                                                                     const std::shared_ptr<Menu::View::IMenuSectionViewModel>& searchSectionViewModel,
                                                                     const std::shared_ptr<TagSearch::View::ITagSearchRepository>& tagSearchRepository,
                                                                     const std::shared_ptr<Modality::View::IModalBackgroundView>& modalBackgroundView,
                                                                     const std::shared_ptr<Modality::View::IModalityController>& modalityController,
                                                                     const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                                     const std::shared_ptr<Reaction::View::IReactionModel>& reactionModel) :
                SearchMenuController(nullptr,
                                     nullptr,
                                     nullptr,
                                     nullptr,
                                     nullptr,
                                     nullptr,
                                     nullptr,
                                     nullptr),

                m_modalityController(modalityController),
                m_messageBus(messageBus),
                m_reactionModel(reactionModel),
                m_poiClosedHandler(this, &DesktopSearchMenuController::OnSearchResultPoiViewClosedMessage),
                m_poiOpenedHandler(this, &DesktopSearchMenuController::OnSearchResultPoiViewOpenedMessage)
            {
                m_menuIdentity = viewModel->GetIdentity();
                
                m_messageBus->SubscribeNative(m_poiClosedHandler);
                m_messageBus->SubscribeNative(m_poiOpenedHandler);
            }

            DesktopSearchMenuController::~DesktopSearchMenuController()
            {
                m_messageBus->UnsubscribeNative(m_poiOpenedHandler);
                m_messageBus->UnsubscribeNative(m_poiClosedHandler);
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