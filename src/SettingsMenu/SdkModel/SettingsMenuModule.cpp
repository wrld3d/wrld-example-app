// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SettingsMenuModule.h"

#include "AboutPageMenuOption.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "MenuSectionViewModel.h"
#include "MenuViewModel.h"
#include "OptionsMenuOption.h"
#include "IReactionControllerModel.h"
#include "SettingsMenu.h"
#include "WeatherMenu.h"
#include "OptionsViewModel.h"
#include "IAboutPageViewModel.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace SdkModel
        {
            namespace
            {
                void AddMenuSection(const std::shared_ptr<View::SettingsMenuViewModel>& viewModel,
                                    const std::string& name,
                                    const std::shared_ptr<Menu::View::IMenuModel>& menuModel,
                                    bool isExpandable)
                {
                    Menu::View::MenuSectionViewModel* pMenuSection = Eegeo_NEW(Menu::View::MenuSectionViewModel)(name, "", menuModel, isExpandable);
                    viewModel->AddSection(*pMenuSection);
                }
            }
            
            void SettingsMenuModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<View::SettingsMenuModel>().singleInstance();
                builder->registerType<View::SettingsMenuOptionsModel>().singleInstance();
                builder->registerType<View::OptionsMenuModel>().singleInstance();
                builder->registerType<View::OptionsMenuOptionsModel>().singleInstance();
                builder->registerType<View::AboutMenuModel>().singleInstance();
                builder->registerType<View::AboutMenuOptionsModel>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     return std::make_shared<View::SettingsMenuViewModel>(false,
                                                                                                   context.resolve<Eegeo::Helpers::IIdentityProvider>(),
                                                                                                   context.resolve<Reaction::View::IReactionControllerModel>());
                                                 }).singleInstance();
            }
            
            void SettingsMenuModule::RegisterLeaves()
            {
                auto viewModel = Resolve<View::SettingsMenuViewModel>();
                auto weatherMenuModel = Resolve<WeatherMenu::View::WeatherMenuModel>();
                AddMenuSection(viewModel, "Weather", weatherMenuModel, true);
                
                auto optionsMenuModel = Resolve<View::OptionsMenuModel>();
                auto optionsMenuOptionsModel = Resolve<View::OptionsMenuOptionsModel>();
                optionsMenuOptionsModel->AddItem("Options", "Options", "", "", Eegeo_NEW(View::OptionsMenuOption)(viewModel, Resolve<Options::View::IOptionsViewModel>()));
                AddMenuSection(viewModel, "Options", optionsMenuModel, false);
                
                auto aboutMenuModel = Resolve<View::AboutMenuModel>();
                auto aboutMenuOptionsModel = Resolve<View::AboutMenuOptionsModel>();
                aboutMenuOptionsModel->AddItem("About", "About", "", "", Eegeo_NEW(View::AboutPageMenuOption)(viewModel, Resolve<AboutPage::View::IAboutPageViewModel>()));
                
                AddMenuSection(viewModel, "About", aboutMenuModel, false);
            }
            
            void SettingsMenuModule::RegisterOpenablesAndReactors()
            {
                RegisterOpenable(Resolve<View::SettingsMenuViewModel>().get());
                RegisterReactor(Resolve<View::SettingsMenuViewModel>().get());
            }
            
            /*
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
            */
        }
    }
}
