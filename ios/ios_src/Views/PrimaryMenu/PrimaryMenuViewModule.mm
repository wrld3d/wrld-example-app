// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PrimaryMenuViewModule.h"
#include "MenuModel.h"
#include "MenuViewModel.h"
#include "MenuViewController.h"
#include "PrimaryMenuView.h"
#include "ScreenProperties.h"

namespace ExampleApp
{
    namespace PrimaryMenu
    {
        PrimaryMenuViewModule::PrimaryMenuViewModule(Menu::IMenuModel& primaryMenuModel,
                                                     Menu::MenuViewModel::IMenuViewModel& primaryMenuViewModel,
                                                     const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                     Modality::IModalityModel& modalitydModel)
        {
            m_pView = [[PrimaryMenuView alloc] initWithDimensions
                       :screenProperties.GetScreenWidth()
                       :screenProperties.GetScreenHeight()
                       :screenProperties.GetPixelScale()
                       ];
            
            m_pMenuViewController = [[MenuViewController alloc] initWithParams:&primaryMenuModel
                                                                              :&primaryMenuViewModel
                                                                              :m_pView
                                                                              :&modalitydModel
                                                                              :false];
        }
        
        PrimaryMenuViewModule::~PrimaryMenuViewModule()
        {
            [m_pMenuViewController release];
            [m_pView release];
        }
        
        MenuViewController& PrimaryMenuViewModule::GetPrimaryMenuViewController() const
        {
            return *m_pMenuViewController;
        }
        
        PrimaryMenuView& PrimaryMenuViewModule::GetPrimaryMenuView() const
        {
            return *m_pView;
        }
    }
}
