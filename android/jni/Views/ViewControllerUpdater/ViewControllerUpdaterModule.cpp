// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ViewControllerUpdaterModule.h"
#include "ViewControllerUpdaterModel.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace ViewControllerUpdater
    {
        ViewControllerUpdaterModule::ViewControllerUpdaterModule()
        {
        	ASSERT_UI_THREAD

        	m_pViewControllerUpdaterModel = Eegeo_NEW(ViewControllerUpdaterModel)();
        }
        
        ViewControllerUpdaterModule::~ViewControllerUpdaterModule()
        {
        	ASSERT_UI_THREAD

            Eegeo_DELETE m_pViewControllerUpdaterModel;
        }
        
        IViewControllerUpdaterModel& ViewControllerUpdaterModule::GetViewControllerUpdaterModel() const
        {
        	ASSERT_UI_THREAD

            return *m_pViewControllerUpdaterModel;
        }
    }
}
