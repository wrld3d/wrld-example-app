// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SecondaryMenuViewModule.h"
#include "IMenuModel.h"
#include "IMenuViewModel.h"
#include "MenuViewController.h"
#include "SearchViewController.h"
#include "SecondaryMenuView.h"
#include "ScreenProperties.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        SecondaryMenuViewModule::SecondaryMenuViewModule(Menu::IMenuModel& secondaryMenuModel,
                                                         Menu::IMenuViewModel& secondaryMenuViewModel,
                                                         const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                         Modality::IModalityModel& modalityModel,
                                                         Search::ISearchQueryPerformer& searchQueryPerformer,
                                                         ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
        {
            m_pView = [[SecondaryMenuView alloc] initWithDimensions
                       :screenProperties.GetScreenWidth()
                       :screenProperties.GetScreenHeight()
                       :screenProperties.GetPixelScale()];
            
            m_pMenuViewController = [[MenuViewController alloc] initWithParams:&secondaryMenuModel
                                                                              :&secondaryMenuViewModel
                                                                              :m_pView
                                                                              :&modalityModel
                                                                              :true];
            
            m_pSearchViewController = [[SearchViewController alloc] initWithParams:[m_pView pSearchEditBox]
                                                                                  :&searchQueryPerformer
                                                                                  :&nativeToUiMessageBus
                                                                                  :&secondaryMenuViewModel];
        }
        
        SecondaryMenuViewModule::~SecondaryMenuViewModule()
        {
            [m_pSearchViewController release];
            [m_pMenuViewController release];
            [m_pView release];
        }
        
        MenuViewController& SecondaryMenuViewModule::GetSecondaryMenuViewController() const
        {
            return *m_pMenuViewController;
        }
        
        SecondaryMenuView& SecondaryMenuViewModule::GetSecondaryMenuView() const
        {
            return *m_pView;
        }
    }
}
