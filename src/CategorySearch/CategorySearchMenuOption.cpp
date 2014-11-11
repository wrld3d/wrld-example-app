// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CategorySearchMenuOption.h"
#include "ISearchQueryPerformer.h"
#include "IMenuViewModel.h"
#include "CategorySearchSelectedMessage.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        CategorySearchMenuOption::CategorySearchMenuOption(CategorySearchModel model,
                                                           ExampleApp::Menu::IMenuViewModel& menuViewModel,
                                                           ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
        : m_model(model)
        , m_menuViewModel(menuViewModel)
        , m_uiToNativeMessageBus(uiToNativeMessageBus)
        {
        }
        
        CategorySearchMenuOption::~CategorySearchMenuOption()
        {
            
        }

        void CategorySearchMenuOption::Select()
        {
        	m_menuViewModel.Close();
        	m_uiToNativeMessageBus.Publish(CategorySearchSelectedMessage(m_model.SearchCategory()));
        }
    }
}
