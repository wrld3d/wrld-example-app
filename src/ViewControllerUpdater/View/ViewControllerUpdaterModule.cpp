// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ViewControllerUpdaterModule.h"
#include "ViewControllerUpdaterModel.h"

namespace ExampleApp
{
    namespace ViewControllerUpdater
    {
        namespace View
        {
            ViewControllerUpdaterModule::ViewControllerUpdaterModule()
            {
                m_pViewControllerUpdaterModel = Eegeo_NEW(ViewControllerUpdaterModel)();
            }

            ViewControllerUpdaterModule::~ViewControllerUpdaterModule()
            {
                Eegeo_DELETE m_pViewControllerUpdaterModel;
            }

            IViewControllerUpdaterModel& ViewControllerUpdaterModule::GetViewControllerUpdaterModel() const
            {
                return *m_pViewControllerUpdaterModel;
            }
        }
    }
}
