// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsMenuModule.h"

#include "OptionsMenuOption.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "MenuViewModel.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            OptionsMenuModule::OptionsMenuModule(Menu::View::IMenuViewModel& menuViewModel,
                                                   Options::View::IOptionsViewModel& OptionsViewModel)
            {

                m_pOptionsMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pOptionsMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pOptionsMenuModel);
                m_pOptionsMenuOptionsModel->AddItem("About", "About", "", "", Eegeo_NEW(View::OptionsMenuOption)(menuViewModel, OptionsViewModel));
            }

            OptionsMenuModule::~OptionsMenuModule()
            {
                Eegeo_DELETE m_pOptionsMenuOptionsModel;
                Eegeo_DELETE m_pOptionsMenuModel;
            }

            Menu::View::IMenuModel& OptionsMenuModule::GetOptionsMenuModel() const
            {
                return *m_pOptionsMenuModel;
            }
        }
    }
}
