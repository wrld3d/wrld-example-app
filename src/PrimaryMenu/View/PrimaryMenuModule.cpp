// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PrimaryMenuModule.h"
#include "MenuModel.h"
#include "MenuViewModel.h"
#include "MenuOptionsModel.h"
#include "MenuSectionViewModel.h"
#include "IPlaceJumpsModule.h"
#include "AboutPageMenuOption.h"
#include "OptionsMenuOption.h"

namespace ExampleApp
{
    namespace PrimaryMenu
    {
        namespace View
        {
            PrimaryMenuModule::PrimaryMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                 AboutPage::View::IAboutPageViewModel& aboutPageViewModel,
                                                 Options::View::IOptionsViewModel& optionsViewModel,
                                                 Reaction::View::IReactionControllerModel& reactionControllerModel)
            {
                m_pModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pModel);

                m_pViewModel = Eegeo_NEW(Menu::View::MenuViewModel)(false,
                               identityProvider.GetNextIdentity(),
                               reactionControllerModel);

                m_pMenuOptionsModel->AddItem("About", "About", "", "misc", Eegeo_NEW(AboutPageMenuOption)(*m_pViewModel, aboutPageViewModel));
                
                m_pMenuOptionsModel->AddItem("Options", "Options", "", "options", Eegeo_NEW(OptionsMenuOption)(*m_pViewModel, optionsViewModel));

                m_pMenuSectionMisc = Eegeo_NEW(Menu::View::MenuSectionViewModel)("Misc", "misc", *m_pModel, false);

                m_pViewModel->AddSection(*m_pMenuSectionMisc);
            }

            PrimaryMenuModule::~PrimaryMenuModule()
            {
                for (std::vector<Menu::View::IMenuSectionViewModel*>::iterator it = m_sections.begin(); it != m_sections.end(); ++it)
                {
                    Eegeo_DELETE *it;
                }

                Eegeo_DELETE m_pMenuSectionMisc;
                Eegeo_DELETE m_pViewModel;
                Eegeo_DELETE m_pMenuOptionsModel;
                Eegeo_DELETE m_pModel;
            }

            void PrimaryMenuModule::AddMenuSection(const std::string& name, const std::string& icon, Menu::View::IMenuModel& menuModel, bool isExpandable)
            {
                Menu::View::MenuSectionViewModel* pMenuSection = Eegeo_NEW(Menu::View::MenuSectionViewModel)(name, icon, menuModel, isExpandable);
                m_pViewModel->AddSection(*pMenuSection);
                m_sections.push_back(pMenuSection);
            }

            Menu::View::IMenuModel& PrimaryMenuModule::GetPrimaryMenuModel() const
            {
                return *m_pModel;
            }

            Menu::View::IMenuOptionsModel& PrimaryMenuModule::GetPrimaryMenuOptionsModel() const
            {
                return *m_pMenuOptionsModel;
            }

            Menu::View::IMenuViewModel& PrimaryMenuModule::GetPrimaryMenuViewModel() const
            {
                return *m_pViewModel;
            }
        }
    }
}
