// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidNativeState.h"
#include "Menu.h"
#include "SecondaryMenuViewModule.h"
#include "SecondaryMenuViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
    	SecondaryMenuViewModule::SecondaryMenuViewModule(
    		const std::string& viewName,
			AndroidNativeState& nativeState,
			Menu::IMenuModel& menuModel,
			Menu::IMenuViewModel& menuViewModel,
			ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
			ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus
		)
        {
    		ASSERT_UI_THREAD

            m_pMenuViewController = Eegeo_NEW(SecondaryMenuViewController)(
				viewName,
				nativeState,
				menuModel,
				menuViewModel,
				uiToNativeMessageBus,
				nativeToUiMessageBus
			);
        }
        
    	SecondaryMenuViewModule::~SecondaryMenuViewModule()
        {
    		ASSERT_UI_THREAD

            Eegeo_DELETE m_pMenuViewController;
        }
        
        Menu::IMenuViewController& SecondaryMenuViewModule::GetMenuViewController() const
        {
        	ASSERT_UI_THREAD

            return *m_pMenuViewController;
        }
    }
}
