// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SettingsMenuModule.h"

#include "AboutPageMenuOption.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "MenuSectionViewModel.h"
#include "MenuViewModel.h"
#include "OptionsMenuOption.h"
#include "IReactionControllerModel.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace SdkModel
        {
            class SettingsMenuModel : public Menu::View::MenuModel
            {
            };
            
            class OptionsMenuModel : public Menu::View::MenuModel
            {
            };
            
            class AboutMenuModel : public Menu::View::MenuModel
            {
            };
            
            class SettingsMenuOptionsModel : public Menu::View::MenuOptionsModel
            {
            public:
                SettingsMenuOptionsModel(const std::shared_ptr<SettingsMenuModel>& settingsMenuModel) : Menu::View::MenuOptionsModel(*settingsMenuModel)
                {
                }
            };
            
            class OptionsMenuOptionsModel : public Menu::View::MenuOptionsModel
            {
            public:
                OptionsMenuOptionsModel(const std::shared_ptr<OptionsMenuModel>& optionsMenuModel) : Menu::View::MenuOptionsModel(*optionsMenuModel)
                {
                }
            };
            
            class AboutMenuOptionsModel : public Menu::View::MenuOptionsModel
            {
            public:
                AboutMenuOptionsModel(const std::shared_ptr<AboutMenuModel>& aboutMenuModel) : Menu::View::MenuOptionsModel(*aboutMenuModel)
                {
                }
            };
            
            class SettingsMenuViewModel : public Menu::View::MenuViewModel
            {
            public:
                SettingsMenuViewModel(bool isInitiallyOnScreen,
                                      const std::shared_ptr<Eegeo::Helpers::IIdentityProvider>& identity,
                                      const std::shared_ptr<Reaction::View::IReactionControllerModel>& reactionControllerModel)
                : Menu::View::MenuViewModel(isInitiallyOnScreen, identity->GetNextIdentity(), reactionControllerModel)
                {
                }
            };
            
            void SettingsMenuModule::Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            {
                builder->registerType<SettingsMenuModel>().singleInstance();
                builder->registerType<SettingsMenuOptionsModel>().singleInstance();
                builder->registerType<OptionsMenuModel>().singleInstance();
                builder->registerType<OptionsMenuOptionsModel>().singleInstance();
                builder->registerType<AboutMenuModel>().singleInstance();
                builder->registerType<AboutMenuOptionsModel>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     return std::make_shared<SettingsMenuViewModel>(false,
                                                                                                   context.resolve<Eegeo::Helpers::IIdentityProvider>(),
                                                                                                   context.resolve<Reaction::View::IReactionControllerModel>());
                                                 }).singleInstance();
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
