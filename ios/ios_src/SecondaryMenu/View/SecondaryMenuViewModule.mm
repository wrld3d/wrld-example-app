// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SecondaryMenuViewModule.h"
#include "SecondaryMenuView.h"
#include "ScreenProperties.h"
#include "MenuViewInterop.h"
#include "SecondaryMenuViewInterop.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace View
        {
            SecondaryMenuViewModule::SecondaryMenuViewModule(Menu::View::IMenuModel& secondaryMenuModel,
                    Menu::View::IMenuViewModel& secondaryMenuViewModel,
                    const Eegeo::Rendering::ScreenProperties& screenProperties,
                    ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pDataProvider = [CustomTableDataProvider alloc];

                m_pView = [[SecondaryMenuView alloc] initWithParams
                           :screenProperties.GetScreenWidth()
                           :screenProperties.GetScreenHeight()
                           :screenProperties.GetPixelScale()
                           :true
                           :secondaryMenuViewModel.SectionsCount()
                           :secondaryMenuViewModel.NumberOfCells()
                           :m_pDataProvider];

                m_pController = Eegeo_NEW(SecondaryMenuController)( *[m_pView getSecondaryMenuInterop],
                                *[m_pView getInterop],
                                secondaryMenuModel,
                                secondaryMenuViewModel,
                                messageBus
                                                                  );
            }

            SecondaryMenuViewModule::~SecondaryMenuViewModule()
            {

                Eegeo_DELETE m_pController;
                [m_pView release];
                [m_pDataProvider release];
            }

            Menu::View::MenuController& SecondaryMenuViewModule::GetMenuController() const
            {
                return *m_pController;
            }

            SecondaryMenuView& SecondaryMenuViewModule::GetSecondaryMenuView() const
            {
                return *m_pView;
            }
        }
    }
}
