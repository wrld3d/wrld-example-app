// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

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
        namespace SdkModel
        {
            SecondaryMenuModule::SecondaryMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                    Reaction::View::IReactionControllerModel& reactionControllerModel,
                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                    ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pModel);

                m_pViewModel = Eegeo_NEW(Menu::View::MenuViewModel)(false,
                               identityProvider.GetNextIdentity(),
                               reactionControllerModel);

                AddMenuSection("Secondary", "", *m_pModel, false);

                m_pPerformedSearchMessageHandler = Eegeo_NEW(PerformedSearchMessageHandler)(
                                                       searchQueryPerformer,
                                                       messageBus
                                                   );
            }

            SecondaryMenuModule::~SecondaryMenuModule()
            {
                Eegeo_DELETE m_pPerformedSearchMessageHandler;

                for(std::vector<Menu::View::IMenuSectionViewModel*>::iterator it = m_sections.begin(); it != m_sections.end(); ++ it)
                {
                    Eegeo_DELETE *it;
                }

                Eegeo_DELETE m_pViewModel;
                Eegeo_DELETE m_pMenuOptionsModel;
                Eegeo_DELETE m_pModel;
            }

            void SecondaryMenuModule::AddMenuSection(const std::string& name, const std::string& icon, Menu::View::IMenuModel& menuModel, bool isExpandable)
            {
                Menu::View::MenuSectionViewModel* pMenuSection = Eegeo_NEW(Menu::View::MenuSectionViewModel)(name, icon, menuModel, isExpandable);
                m_pViewModel->AddSection(*pMenuSection);
                m_sections.push_back(pMenuSection);
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
