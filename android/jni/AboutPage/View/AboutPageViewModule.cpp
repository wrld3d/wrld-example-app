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
        		ASSERT_UI_THREAD
        		builder->registerType<AboutPageView>().as<IAboutPageView>().singleInstance();
        	}
        }
    }
}
