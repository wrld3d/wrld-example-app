// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ViewControllerUpdaterModule.h"
#include "ViewControllerUpdaterModel.h"

namespace ExampleApp
{
    namespace ViewControllerUpdater
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
