// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <algorithm>
#include "ViewControllerUpdaterModel.h"
#include "IUpdateableViewController.h"

namespace ExampleApp
{
    namespace ViewControllerUpdater
    {
        ViewControllerUpdaterModel::ViewControllerUpdaterModel()
        {
            
        }
        
        ViewControllerUpdaterModel::~ViewControllerUpdaterModel()
        {
            
        }
        
        void ViewControllerUpdaterModel::AddUpdateableObject(IUpdateableViewController& updateableViewController)
        {
            m_updateTargets.push_back(&updateableViewController);
        }
        
        void ViewControllerUpdaterModel::RemoveUpdateableObject(IUpdateableViewController& updateableViewController)
        {
            m_updateTargets.erase(std::remove(m_updateTargets.begin(), m_updateTargets.end(), &updateableViewController), m_updateTargets.end());
        }
        
        void ViewControllerUpdaterModel::UpdateObjects(float deltaSeconds)
        {
            for(std::vector<IUpdateableViewController*>::iterator it = m_updateTargets.begin(); it != m_updateTargets.end(); ++ it)
            {
            	IUpdateableViewController& updatable =**it;
            	updatable.Update(deltaSeconds);
            }
        }
    }
}
