// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <string>
#include <vector>
#include "CategorySearchModule.h"
#include "CategorySearchModel.h"
#include "CategorySearchMenuOption.h"
#include "CategorySearchRepository.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "CategorySearchSelectedMessageHandler.h"

namespace
{
    std::vector<ExampleApp::CategorySearch::CategorySearchModel> GetDeCartaCategories()
    {
        // Some decarta categories from http://developer.decarta.com/Docs/REST/Search#category
        std::vector<ExampleApp::CategorySearch::CategorySearchModel> categories;
        categories.push_back(ExampleApp::CategorySearch::CategorySearchModel("Coffee", "coffee shop", "coffee"));
        categories.push_back(ExampleApp::CategorySearch::CategorySearchModel("Food", "restaurant", "food"));
        categories.push_back(ExampleApp::CategorySearch::CategorySearchModel("Nightlife", "night life", "nightlife"));
        categories.push_back(ExampleApp::CategorySearch::CategorySearchModel("Arts", "museum", "arts"));
        categories.push_back(ExampleApp::CategorySearch::CategorySearchModel("Hotels", "hotel", "hotel"));
        categories.push_back(ExampleApp::CategorySearch::CategorySearchModel("Parks", "park", "park"));
        categories.push_back(ExampleApp::CategorySearch::CategorySearchModel("Banks", "bank", "bank"));
        return categories;
    }
}

namespace ExampleApp
{
    namespace CategorySearch
    {
        CategorySearchModule::CategorySearchModule(Search::ISearchQueryPerformer& searchQueryPerformer,
                                                   ExampleApp::Menu::IMenuViewModel& menuViewModel,
                                                   ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
        {
            m_pMenuModel = Eegeo_NEW(Menu::MenuModel)();
            m_pMenuOptionsModel = Eegeo_NEW(Menu::MenuOptionsModel)(*m_pMenuModel);
            
            std::vector<CategorySearchModel> categories = GetDeCartaCategories();
            
            m_pCategorySearchRepository = Eegeo_NEW(CategorySearchRepository)(categories);
            
            for(std::vector<CategorySearchModel>::iterator it = categories.begin(); it != categories.end(); it++)
            {
                CategorySearchModel& categorySearchModel = *it;
            
                m_pMenuOptionsModel->AddItem(categorySearchModel.Name(),
                                             categorySearchModel.Name(),
                                             "",
                                             categorySearchModel.Icon(),
                                             Eegeo_NEW(CategorySearchMenuOption)(categorySearchModel, menuViewModel, uiToNativeMessageBus));
            }


            m_pCategorySearchSelectedMessageHandler = Eegeo_NEW(CategorySearchSelectedMessageHandler)(
				searchQueryPerformer,
				uiToNativeMessageBus
            );
        }
        
        CategorySearchModule::~CategorySearchModule()
        {
        	Eegeo_DELETE m_pCategorySearchSelectedMessageHandler;
            Eegeo_DELETE m_pMenuOptionsModel;
            Eegeo_DELETE m_pMenuModel;
            Eegeo_DELETE m_pCategorySearchRepository;
        }
        
        Menu::IMenuModel& CategorySearchModule::GetCategorySearchMenuModel() const
        {
            return *m_pMenuModel;
        }
        
        ICategorySearchRepository& CategorySearchModule::GetCategorySearchRepository() const
        {
            return *m_pCategorySearchRepository;
        }
    }
}
