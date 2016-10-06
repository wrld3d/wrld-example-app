// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsViewModule.h"
#include "Options.h"
#include "OptionsView.h"
#include "OptionsController.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "IHttpCache.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
			void OptionsViewModule::Register(const TContainerBuilder& builder)
			{
				builder->registerType<OptionsView>().as<IOptionsView>().singleInstance();
			}

			void OptionsViewModule::RegisterUiLeaves()
			{
				Eegeo_TTY("OptionsViewModule::RegisterUiLeaves begin");
				ASSERT_UI_THREAD
				RegisterLeaf<IOptionsView>();
				Eegeo_TTY("OptionsViewModule::RegisterUiLeaves end");
			}
        }
    }
}
