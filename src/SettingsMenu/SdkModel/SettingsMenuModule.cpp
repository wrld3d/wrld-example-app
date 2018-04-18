// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SettingsMenuModule.h"

#include "AboutPageMenuOption.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "MenuViewModel.h"
#include "OptionsMenuOption.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace SdkModel
        {
            SettingsMenuModule::SettingsMenuModule(Menu::View::IMenuViewModel& menuViewModel,
                                                   AboutPage::View::IAboutPageViewModel& aboutPageViewModel,
                                                   Options::View::IOptionsViewModel& optionsViewModel)
            {

                m_pAboutMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pAboutMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pAboutMenuModel);
                m_pAboutMenuOptionsModel->AddItem("About", "About", "", "", Eegeo_NEW(View::AboutPageMenuOption)(menuViewModel, aboutPageViewModel));

                m_pOptionsMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pOptionsMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pOptionsMenuModel);
                m_pOptionsMenuOptionsModel->AddItem("Options", "Options", "", "", Eegeo_NEW(View::OptionsMenuOption)(menuViewModel, optionsViewModel));
            }
            
            SettingsMenuModule::~SettingsMenuModule()
            {
                Eegeo_DELETE m_pAboutMenuOptionsModel;
                Eegeo_DELETE m_pAboutMenuModel;

                Eegeo_DELETE m_pOptionsMenuOptionsModel;
                Eegeo_DELETE m_pOptionsMenuModel;
            }

            Menu::View::IMenuModel& SettingsMenuModule::GetAboutMenuModel() const
            {
                return *m_pAboutMenuModel;
            }

            Menu::View::IMenuModel& SettingsMenuModule::GetOptionsMenuModel() const
            {
                return *m_pOptionsMenuModel;
            }
        }
    }
}
