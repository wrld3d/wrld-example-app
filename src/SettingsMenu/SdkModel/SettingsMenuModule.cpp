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
                                                   Options::View::IOptionsViewModel& optionsViewModel)
            {
                m_pOptionsMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pOptionsMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pOptionsMenuModel);
                m_pOptionsMenuOptionsModel->AddItem("Options", "Options", "", "", Eegeo_NEW(View::OptionsMenuOption)(menuViewModel, optionsViewModel));
            }
            
            SettingsMenuModule::~SettingsMenuModule()
            {
                Eegeo_DELETE m_pOptionsMenuOptionsModel;
                Eegeo_DELETE m_pOptionsMenuModel;
            }

            Menu::View::IMenuModel& SettingsMenuModule::GetOptionsMenuModel() const
            {
                return *m_pOptionsMenuModel;
            }
        }
    }
}
