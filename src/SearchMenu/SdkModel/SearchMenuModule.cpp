// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuModule.h"

#include "IReactionControllerModel.h"
#include "MenuModel.h"
#include "MenuViewModel.h"
#include "MenuOptionsModel.h"
#include "MenuSectionViewModel.h"
#include "SearchMenuPerformedSearchMessageHandler.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace SdkModel
        {
            SearchMenuModule::SearchMenuModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                               ExampleApp::Reaction::View::IReactionControllerModel& reactionControllerModel,
                                               Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                               ExampleAppMessaging::TMessageBus& messageBus,
                                               Metrics::IMetricsService& metricsService)
            : m_pMenuModel(NULL)
            , m_pMenuOptionsModel(NULL)
            , m_pMenuViewModel(NULL)
            , m_pSearchSectionViewModel(NULL)
            , m_pPerformedSearchMessageHandler(NULL)
            {
                m_pMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pMenuModel);
                
                m_pMenuViewModel = Eegeo_NEW(Menu::View::MenuViewModel)(false,
                                                                        identityProvider.GetNextIdentity(),
                                                                        reactionControllerModel);
                
                m_pPerformedSearchMessageHandler = Eegeo_NEW(SearchMenuPerformedSearchMessageHandler)(searchQueryPerformer,
                                                                                                      messageBus,
                                                                                                      metricsService);
            }
            
            SearchMenuModule::~SearchMenuModule()
            {
                Eegeo_DELETE m_pPerformedSearchMessageHandler;
                
                for(std::vector<Menu::View::IMenuSectionViewModel*>::iterator it = m_sections.begin(); it != m_sections.end(); ++ it)
                {
                    Eegeo_DELETE *it;
                }
                
                Eegeo_DELETE m_pSearchSectionViewModel;
                Eegeo_DELETE m_pMenuViewModel;
                Eegeo_DELETE m_pMenuOptionsModel;
                Eegeo_DELETE m_pMenuModel;
            }
            
            void SearchMenuModule::SetSearchSection(const std::string& name,
                                                    Menu::View::IMenuModel& menuModel)
            {
                m_pSearchSectionViewModel = Eegeo_NEW(Menu::View::MenuSectionViewModel)(name, "", menuModel, false);
            }
            
            void SearchMenuModule::AddMenuSection(const std::string& name,
                                                  Menu::View::IMenuModel& menuModel,
                                                  bool isExpandable)
            {
                Menu::View::MenuSectionViewModel* pMenuSection = Eegeo_NEW(Menu::View::MenuSectionViewModel)(name, "", menuModel, isExpandable);
                m_pMenuViewModel->AddSection(*pMenuSection);
                m_sections.push_back(pMenuSection);
            }
            
            Menu::View::IMenuModel& SearchMenuModule::GetSearchMenuModel() const
            {
                return *m_pMenuModel;
            }
            
            Menu::View::IMenuOptionsModel& SearchMenuModule::GetSearchMenuOptionsModel() const
            {
                return *m_pMenuOptionsModel;
            }
            
            Menu::View::IMenuViewModel& SearchMenuModule::GetSearchMenuViewModel() const
            {
                return *m_pMenuViewModel;
            }
            
            Menu::View::IMenuSectionViewModel& SearchMenuModule::GetSearchSectionViewModel() const
            {
                Eegeo_ASSERT(m_pSearchSectionViewModel != NULL, "Search section view model not set, please call SetSearchSection before calling this function");
                
                return *m_pSearchSectionViewModel;
            }
        }
    }
}