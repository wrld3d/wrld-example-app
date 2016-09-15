// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuModule.h"

#include "IReactionControllerModel.h"
#include "MenuModel.h"
#include "MenuViewModel.h"
#include "MenuOptionsModel.h"
#include "MenuSectionViewModel.h"
#include "SearchMenuPerformedSearchMessageHandler.h"
#include "SearchMenuOptions.h"
#include "PlaceJumpMenuOption.h"
#include "TagSearchMenuOption.h"
#include "MyPinMenuOption.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace SdkModel
        {
            void SearchMenuModule::Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            {
                builder->registerType<View::SearchMenuModel>().singleInstance();
                builder->registerType<View::SearchMenuOptionsModel>().singleInstance();
                builder->registerType<View::SearchMenuViewModel>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     return std::make_shared<View::SearchMenuSectionViewModel>("Search Results", "", context.resolve<SearchResultSection::View::SearchResultSectionMenuModel>(), false);
                                                 }).singleInstance();
                builder->registerType<SearchMenuPerformedSearchMessageHandler>();
            }
            
            void SearchMenuModule::RegisterLeaves()
            {
                RegisterLeaf<SearchMenuPerformedSearchMessageHandler>();
                
                auto viewModel = Resolve<View::SearchMenuViewModel>();
                Menu::View::MenuSectionViewModel* pTagSearchSection = Eegeo_NEW(Menu::View::MenuSectionViewModel)("Find", "", Resolve<TagSearch::View::TagSearchMenuModel>(), true);
                viewModel->AddSection(*pTagSearchSection);

                Menu::View::MenuSectionViewModel* pPlaceJumpSection = Eegeo_NEW(Menu::View::MenuSectionViewModel)("Locations", "", Resolve<PlaceJumps::View::PlaceJumpMenuModel>(), true);
                viewModel->AddSection(*pPlaceJumpSection);
                
                Menu::View::MenuSectionViewModel* pMyPinsSection = Eegeo_NEW(Menu::View::MenuSectionViewModel)("My Pins", "", Resolve<MyPins::View::MyPinsMenuModel>(), true);
                viewModel->AddSection(*pMyPinsSection);
            }
            
            void SearchMenuModule::RegisterOpenablesAndReactors()
            {
                RegisterOpenable(Resolve<View::SearchMenuViewModel>().get());
                RegisterReactor(Resolve<View::SearchMenuViewModel>().get());
            }
            
            /*
             
            TODO: fix up this...
             
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
             
            Menu::View::IMenuSectionViewModel& SearchMenuModule::GetSearchSectionViewModel() const
            {
                Eegeo_ASSERT(m_pSearchSectionViewModel != NULL, "Search section view model not set, please call SetSearchSection before calling this function");
                
                return *m_pSearchSectionViewModel;
            }
             */
        }
    }
}