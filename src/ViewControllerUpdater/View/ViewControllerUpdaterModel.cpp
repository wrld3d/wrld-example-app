// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <algorithm>
#include "ViewControllerUpdaterModel.h"
#include "IUpdateableViewController.h"

namespace ExampleApp
{
    namespace ViewControllerUpdater
    {
        namespace View
        {
            ViewControllerUpdaterModel::ViewControllerUpdaterModel()
            {
            }

            ViewControllerUpdaterModel::~ViewControllerUpdaterModel()
            {
            }

            void ViewControllerUpdaterModel::AddUpdateableObject(IUpdateableViewController& updateableViewController)
            {
                m_updateTargetsUi.push_back(&updateableViewController);
            }

            void ViewControllerUpdaterModel::RemoveUpdateableObject(IUpdateableViewController& updateableViewController)
            {
                m_updateTargetsUi.erase(std::remove(m_updateTargetsUi.begin(), m_updateTargetsUi.end(), &updateableViewController), m_updateTargetsUi.end());
            }

            void ViewControllerUpdaterModel::UpdateObjectsUiThread(float deltaSeconds)
            {
                for(std::vector<IUpdateableViewController*>::iterator it = m_updateTargetsUi.begin(); it != m_updateTargetsUi.end(); ++ it)
                {
                    IUpdateableViewController& updatable =**it;
                    updatable.UpdateUiThread(deltaSeconds);
                }
            }
        }
    }
}
