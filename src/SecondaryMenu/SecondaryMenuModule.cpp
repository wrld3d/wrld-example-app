// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SecondaryMenuModule.h"
#include "MenuModel.h"
#include "MenuViewModel.h"
#include "MenuOptionsModel.h"
#include "MenuSectionViewModel.h"
#include "PerformedSearchMessageHandler.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        SecondaryMenuModule::SecondaryMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                 Reaction::IReactionControllerModel& reactionControllerModel,
                                                 Search::ISearchQueryPerformer& searchQueryPerformer,
                                                 ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
        {
            m_pModel = Eegeo_NEW(Menu::MenuModel)();
            m_pMenuOptionsModel = Eegeo_NEW(Menu::MenuOptionsModel)(*m_pModel);

            m_pViewModel = Eegeo_NEW(Menu::MenuViewModel)(false,
                                                          identityProvider.GetNextIdentity(),
                                                          reactionControllerModel);
            
            AddMenuSection("Secondary", "", *m_pModel, false);

            m_pPerformedSearchMessageHandler = Eegeo_NEW(PerformedSearchMessageHandler)(
				searchQueryPerformer,
				uiToNativeMessageBus
            );
        }
        
        SecondaryMenuModule::~SecondaryMenuModule()
        {
        	Eegeo_DELETE m_pPerformedSearchMessageHandler;

            for(std::vector<Menu::IMenuSectionViewModel*>::iterator it = m_sections.begin(); it != m_sections.end(); ++ it)
            {
                Eegeo_DELETE *it;
            }
            
            Eegeo_DELETE m_pViewModel;
            Eegeo_DELETE m_pMenuOptionsModel;
            Eegeo_DELETE m_pModel;
        }
        
        void SecondaryMenuModule::AddMenuSection(const std::string& name, const std::string& icon, Menu::IMenuModel& menuModel, bool isExpandable)
        {
            Menu::MenuSectionViewModel* pMenuSection = Eegeo_NEW(Menu::MenuSectionViewModel)(name, icon, menuModel, isExpandable);
            m_pViewModel->AddSection(*pMenuSection);
            m_sections.push_back(pMenuSection);
        }
        
        Menu::IMenuModel& SecondaryMenuModule::GetSecondaryMenuModel() const
        {
            return *m_pModel;
        }
        
        Menu::IMenuOptionsModel& SecondaryMenuModule::GetSecondaryMenuOptionsModel() const
        {
            return *m_pMenuOptionsModel;
        }
        
        Menu::IMenuViewModel& SecondaryMenuModule::GetSecondaryMenuViewModel() const
        {
            return *m_pViewModel;
        }
    }
}
