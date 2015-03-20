// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SecondaryMenuModule.h"
#include "MenuModel.h"
#include "MenuViewModel.h"
#include "MenuOptionsModel.h"
#include "MenuSectionViewModel.h"
#include "PerformedSearchMessageHandler.h"
#include "AboutPageMenuOption.h"
#include "OptionsMenuOption.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace SdkModel
        {
            SecondaryMenuModule::SecondaryMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                     Reaction::View::IReactionControllerModel& reactionControllerModel,
                                                     Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                     ExampleAppMessaging::TMessageBus& messageBus,
                                                     AboutPage::View::IAboutPageViewModel& aboutPageViewModel,
                                                     Options::View::IOptionsViewModel& optionsViewModel,
                                                     Metrics::IMetricsService& metricsService)
            {
                m_pModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pModel);
                
                m_pViewModel = Eegeo_NEW(Menu::View::MenuViewModel)(false,
                                                                    identityProvider.GetNextIdentity(),
                                                                    reactionControllerModel);
                
                AddMenuSection("Secondary", *m_pModel, false);
                
                m_pPerformedSearchMessageHandler = Eegeo_NEW(PerformedSearchMessageHandler)(searchQueryPerformer,
                                                                                            messageBus,
                                                                                            metricsService);
                
                
                m_pSettingsModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pSettingsMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pSettingsModel);
                m_pSettingsMenuOptionsModel->AddItem("About", "About", "", "misc", Eegeo_NEW(View::AboutPageMenuOption)(*m_pViewModel,aboutPageViewModel));
                m_pSettingsMenuOptionsModel->AddItem("Options", "Options", "", "options", Eegeo_NEW(View::OptionsMenuOption)(*m_pViewModel, optionsViewModel));
            }
            
            SecondaryMenuModule::~SecondaryMenuModule()
            {
                Eegeo_DELETE m_pSettingsMenuOptionsModel;
                Eegeo_DELETE m_pSettingsModel;
                
                Eegeo_DELETE m_pPerformedSearchMessageHandler;
                
                for(std::vector<Menu::View::IMenuSectionViewModel*>::iterator it = m_sections.begin(); it != m_sections.end(); ++ it)
                {
                    Eegeo_DELETE *it;
                }
                
                Eegeo_DELETE m_pViewModel;
                Eegeo_DELETE m_pMenuOptionsModel;
                Eegeo_DELETE m_pModel;
            }
            
            void SecondaryMenuModule::AddMenuSection(const std::string& name,
                                                     Menu::View::IMenuModel& menuModel,
                                                     bool isExpandable)
            {
                Menu::View::MenuSectionViewModel* pMenuSection = Eegeo_NEW(Menu::View::MenuSectionViewModel)(name, "", menuModel, isExpandable);
                m_pViewModel->AddSection(*pMenuSection);
                m_sections.push_back(pMenuSection);
            }
            
            Menu::View::IMenuModel& SecondaryMenuModule::GetSettingsMenuModel() const
            {
                return *m_pSettingsModel;
            }
            
            Menu::View::IMenuModel& SecondaryMenuModule::GetSecondaryMenuModel() const
            {
                return *m_pModel;
            }
            
            Menu::View::IMenuOptionsModel& SecondaryMenuModule::GetSecondaryMenuOptionsModel() const
            {
                return *m_pMenuOptionsModel;
            }
            
            Menu::View::IMenuViewModel& SecondaryMenuModule::GetSecondaryMenuViewModel() const
            {
                return *m_pViewModel;
            }
        }
    }
}
