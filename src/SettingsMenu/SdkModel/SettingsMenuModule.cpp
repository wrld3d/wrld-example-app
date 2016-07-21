// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SettingsMenuModule.h"

#include "AboutPageMenuOption.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "MenuSectionViewModel.h"
#include "MenuViewModel.h"
#include "OptionsMenuOption.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace SdkModel
        {
            SettingsMenuModule::SettingsMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                   Reaction::View::IReactionControllerModel& reactionControllerModel,
                                                   AboutPage::View::IAboutPageViewModel& aboutPageViewModel,
                                                   Options::View::IOptionsViewModel& optionsViewModel,
                                                   Menu::View::IMenuModel& weatherMenuModel)
            {
                m_pModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pModel);
                
                m_pViewModel = Eegeo_NEW(Menu::View::MenuViewModel)(false,
                                                                    identityProvider.GetNextIdentity(),
                                                                    reactionControllerModel);

                AddMenuSection("Weather", weatherMenuModel, true);
                
                m_pOptionsMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pOptionsMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pOptionsMenuModel);
                m_pOptionsMenuOptionsModel->AddItem("Options", "Options", "", "", Eegeo_NEW(View::OptionsMenuOption)(*m_pViewModel, optionsViewModel));
                
                AddMenuSection("Options", *m_pOptionsMenuModel, false);

                m_pAboutMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pAboutMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pAboutMenuModel);
                m_pAboutMenuOptionsModel->AddItem("About", "About", "", "", Eegeo_NEW(View::AboutPageMenuOption)(*m_pViewModel, aboutPageViewModel));

                AddMenuSection("About", *m_pAboutMenuModel, false);
                
            }
            
            SettingsMenuModule::~SettingsMenuModule()
            {
                Eegeo_DELETE m_pOptionsMenuOptionsModel;
                Eegeo_DELETE m_pOptionsMenuModel;
                
                Eegeo_DELETE m_pAboutMenuOptionsModel;
                Eegeo_DELETE m_pAboutMenuModel;
                
                for(std::vector<Menu::View::IMenuSectionViewModel*>::iterator it = m_sections.begin(); it != m_sections.end(); ++ it)
                {
                    Eegeo_DELETE *it;
                }
                
                Eegeo_DELETE m_pViewModel;
                Eegeo_DELETE m_pMenuOptionsModel;
                Eegeo_DELETE m_pModel;
            }
            
            void SettingsMenuModule::AddMenuSection(const std::string& name,
                                                    Menu::View::IMenuModel& menuModel,
                                                    bool isExpandable)
            {
                Menu::View::MenuSectionViewModel* pMenuSection = Eegeo_NEW(Menu::View::MenuSectionViewModel)(name, "", menuModel, isExpandable);
                m_pViewModel->AddSection(*pMenuSection);
                m_sections.push_back(pMenuSection);
            }
            
            Menu::View::IMenuModel& SettingsMenuModule::GetSettingsMenuModel() const
            {
                return *m_pModel;
            }
            
            Menu::View::IMenuOptionsModel& SettingsMenuModule::GetSettingsMenuOptionsModel() const
            {
                return *m_pMenuOptionsModel;
            }
            
            Menu::View::IMenuViewModel& SettingsMenuModule::GetSettingsMenuViewModel() const
            {
                return *m_pViewModel;
            }
        }
    }
}
