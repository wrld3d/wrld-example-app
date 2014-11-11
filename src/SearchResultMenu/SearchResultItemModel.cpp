// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultItemModel.h"
#include "SearchResultModel.h"
#include "ICameraTransitionController.h"
#include "Logger.h"
#include "SearchResultMenuItemSelectedMessage.h"


namespace ExampleApp
{
    namespace SearchResultMenu
    {
        SearchResultItemModel::SearchResultItemModel(const std::string& name,
                                                     const Eegeo::dv3& searchResultModelLocationEcef,
                                                     OpenableControlViewModel::IOpenableControlViewModel& searchMenuViewModel,
                                                     ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
        : m_name(name)
        , m_searchResultModelLocationEcef(searchResultModelLocationEcef)
        , m_searchMenuViewModel(searchMenuViewModel)
        , m_uiToNativeMessageBus(uiToNativeMessageBus)
        {
            
        }
        
        SearchResultItemModel::~SearchResultItemModel()
        {
            
        }

        void SearchResultItemModel::Select()
        {
             m_searchMenuViewModel.Close();

             m_uiToNativeMessageBus.Publish(SearchResultMenuItemSelectedMessage(
				 m_searchResultModelLocationEcef)
             );
        }
    }
}
