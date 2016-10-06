// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageViewModule.h"
#include "AboutPage.h"
#include "AboutPageView.h"
#include "AboutPageController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
        	void AboutPageViewModule::Register(const TContainerBuilder& builder)
        	{
        		builder->registerType<AboutPageView>().as<IAboutPageView>().singleInstance();
        	}

			void AboutPageViewModule::RegisterUiLeaves()
			{
				Eegeo_TTY("AboutPageViewModule::RegisterUiLeaves begin");
        		ASSERT_UI_THREAD
				RegisterLeaf<IAboutPageView>();
				Eegeo_TTY("AboutPageViewModule::RegisterUiLeaves end");
			}
        }
    }
}
