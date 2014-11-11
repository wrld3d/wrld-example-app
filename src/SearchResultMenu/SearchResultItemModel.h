// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "IMenuOption.h"
#include "Search.h"
#include "CameraTransitions.h"
#include "IOpenableControlViewModel.h"
#include "VectorMath.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        class SearchResultItemModel: public Menu::IMenuOption, private Eegeo::NonCopyable
        {
            std::string m_name;
            Eegeo::dv3 m_searchResultModelLocationEcef;
            OpenableControlViewModel::IOpenableControlViewModel& m_searchMenuViewModel;
            ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
            
        public:
            SearchResultItemModel(const std::string& name,
                                  const Eegeo::dv3& searchResultModelLocationEcef,
                                  OpenableControlViewModel::IOpenableControlViewModel& searchMenuViewModel,
                                  ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);
            
            ~SearchResultItemModel();
            
            void Select();
        };
    }
    
}
