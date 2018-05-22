// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageMenuModule.h"

#include "AboutPageMenuOption.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "MenuViewModel.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace SdkModel
        {
            AboutPageMenuModule::AboutPageMenuModule(Menu::View::IMenuViewModel& menuViewModel,
                                                   AboutPage::View::IAboutPageViewModel& aboutPageViewModel)
            {

                m_pAboutPageMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pAboutPageMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pAboutPageMenuModel);
                m_pAboutPageMenuOptionsModel->AddItem("About", "About", "", "", Eegeo_NEW(View::AboutPageMenuOption)(menuViewModel, aboutPageViewModel));
            }

            AboutPageMenuModule::~AboutPageMenuModule()
            {
                Eegeo_DELETE m_pAboutPageMenuOptionsModel;
                Eegeo_DELETE m_pAboutPageMenuModel;
            }

            Menu::View::IMenuModel& AboutPageMenuModule::GetAboutPageMenuModel() const
            {
                return *m_pAboutPageMenuModel;
            }
        }
    }
}
