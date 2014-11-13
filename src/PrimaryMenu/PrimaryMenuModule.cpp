// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PrimaryMenuModule.h"
#include "MenuModel.h"
#include "MenuViewModel.h"
#include "MenuOptionsModel.h"
#include "MenuSectionViewModel.h"
#include "IPlaceJumpsModule.h"
#include "AboutPageMenuOption.h"

namespace ExampleApp
{
    namespace PrimaryMenu
    {
        PrimaryMenuModule::PrimaryMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                             AboutPage::IAboutPageViewModel& aboutPageViewModel,
                                             Reaction::IReactionControllerModel& reactionControllerModel)
        {
            m_pModel = Eegeo_NEW(Menu::MenuModel)();
            m_pMenuOptionsModel = Eegeo_NEW(Menu::MenuOptionsModel)(*m_pModel);
            
            m_pViewModel = Eegeo_NEW(Menu::MenuViewModel)(false,
                                                          identityProvider.GetNextIdentity(),
                                                          reactionControllerModel);
            
            m_pMenuOptionsModel->AddItem("About", "About", "", "misc", Eegeo_NEW(Options::AboutPageMenuOption)(*m_pViewModel,
                                                                                                               aboutPageViewModel));
            
            m_pMenuSectionMisc = Eegeo_NEW(Menu::MenuSectionViewModel)("Misc", "misc", *m_pModel, false);
            
            m_pViewModel->AddSection(*m_pMenuSectionMisc);
        }
        
        PrimaryMenuModule::~PrimaryMenuModule()
        {
            for (std::vector<Menu::IMenuSectionViewModel*>::iterator it = m_sections.begin(); it != m_sections.end(); ++it)
            {
                Eegeo_DELETE *it;
            }
            
            Eegeo_DELETE m_pMenuSectionMisc;
            Eegeo_DELETE m_pViewModel;
            Eegeo_DELETE m_pMenuOptionsModel;
            Eegeo_DELETE m_pModel;
        }
        
        void PrimaryMenuModule::AddMenuSection(const std::string& name, const std::string& icon, Menu::IMenuModel& menuModel, bool isExpandable)
        {
            Menu::MenuSectionViewModel* pMenuSection = Eegeo_NEW(Menu::MenuSectionViewModel)(name, icon, menuModel, isExpandable);
            m_pViewModel->AddSection(*pMenuSection);
            m_sections.push_back(pMenuSection);
        }
        
        Menu::IMenuModel& PrimaryMenuModule::GetPrimaryMenuModel() const
        {
            return *m_pModel;
        }
        
        Menu::IMenuOptionsModel& PrimaryMenuModule::GetPrimaryMenuOptionsModel() const
        {
            return *m_pMenuOptionsModel;
        }
        
        Menu::IMenuViewModel& PrimaryMenuModule::GetPrimaryMenuViewModel() const
        {
            return *m_pViewModel;
        }
    }
}
