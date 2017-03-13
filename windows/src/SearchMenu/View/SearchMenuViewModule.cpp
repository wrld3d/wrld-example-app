// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuViewModule.h"

#include "WindowsNativeState.h"
#include "ScreenProperties.h"
#include "SearchMenuView.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchMenuViewModule::SearchMenuViewModule(const std::string& viewName,
                                                       WindowsNativeState& nativeState,
                                                       Menu::View::IMenuModel& searchMenuModel,
                                                       Menu::View::IMenuViewModel& searchMenuViewModel,
                                                       Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                                                       TagSearch::View::ITagSearchRepository& tagSearchRepository,
                                                       Modality::View::IModalBackgroundView& modalBackgroundView,
                                                       Modality::View::IModalityController& modalityController,
                                                       ExampleAppMessaging::TMessageBus& messageBus,
                                                       Reaction::View::IReactionModel& reactionModel,
                                                       bool isInKioskMode)
            {
                m_pView = Eegeo_NEW(SearchMenuView)(nativeState, viewName, isInKioskMode);

                m_pController = Eegeo_NEW(DesktopSearchMenuController)(searchMenuModel,
                                                                searchMenuViewModel,
                                                                *m_pView,
                                                                *m_pView,
                                                                searchSectionViewModel,
                                                                tagSearchRepository,
                                                                modalBackgroundView,
                                                                modalityController,
                                                                messageBus,
                                                                reactionModel);
            }

            SearchMenuViewModule::~SearchMenuViewModule()
            {
                Eegeo_DELETE m_pController;
                
                Eegeo_DELETE m_pView;
            }

            Menu::View::MenuController& SearchMenuViewModule::GetMenuController()
            {
                return *m_pController;
            }

            Menu::View::IMenuView& SearchMenuViewModule::GetMenuView()
            {
                return *m_pView;
            }
        }
    }
}
