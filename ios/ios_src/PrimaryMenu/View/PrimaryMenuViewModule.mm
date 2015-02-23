// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PrimaryMenuViewModule.h"
#include "MenuModel.h"
#include "MenuViewModel.h"
#include "PrimaryMenuView.h"
#include "ScreenProperties.h"
#include "MenuController.h"
#include "MenuViewInterop.h"

namespace ExampleApp
{
    namespace PrimaryMenu
    {
        namespace View
        {
            PrimaryMenuViewModule::PrimaryMenuViewModule(Menu::View::IMenuModel& primaryMenuModel,
                    Menu::View::MenuViewModel::IMenuViewModel& primaryMenuViewModel,
                    const Eegeo::Rendering::ScreenProperties& screenProperties,
                    Modality::View::IModalityModel& modalitydModel)
            {
                m_pDataProvider = [CustomTableDataProvider alloc];

                m_pView = [[PrimaryMenuView alloc] initWithParams
                           :screenProperties.GetScreenWidth()
                           :screenProperties.GetScreenHeight()
                           :screenProperties.GetPixelScale()
                           :false
                           :primaryMenuViewModel.SectionsCount()
                           :primaryMenuViewModel.NumberOfCells()
                           :m_pDataProvider
                          ];

                m_pController = Eegeo_NEW(Menu::View::MenuController)(primaryMenuModel,
                                primaryMenuViewModel,
                                *[m_pView getInterop]);
            }

            PrimaryMenuViewModule::~PrimaryMenuViewModule()
            {
                Eegeo_DELETE m_pController;
                [m_pView release];
                [m_pDataProvider release];
            }

            Menu::View::MenuController& PrimaryMenuViewModule::GetMenuController() const
            {
                return *m_pController;
            }

            PrimaryMenuView& PrimaryMenuViewModule::GetPrimaryMenuView() const
            {
                return *m_pView;
            }
        }
    }
}
