// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <algorithm>
#include "ViewControllerUpdaterModel.h"
#include "IUpdateableViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
	namespace ViewControllerUpdater
	{
		ViewControllerUpdaterModel::ViewControllerUpdaterModel()
		{
			ASSERT_UI_THREAD
		}

		ViewControllerUpdaterModel::~ViewControllerUpdaterModel()
		{
			ASSERT_UI_THREAD
		}

		void ViewControllerUpdaterModel::AddUpdateableObject(IUpdateableViewController& updateableViewController)
		{
			ASSERT_UI_THREAD

			m_updateTargetsUi.push_back(&updateableViewController);
		}

		void ViewControllerUpdaterModel::RemoveUpdateableObject(IUpdateableViewController& updateableViewController)
		{
			ASSERT_UI_THREAD

			m_updateTargetsUi.erase(std::remove(m_updateTargetsUi.begin(), m_updateTargetsUi.end(), &updateableViewController), m_updateTargetsUi.end());
		}

		void ViewControllerUpdaterModel::UpdateObjectsUiThread(float deltaSeconds)
		{
			ASSERT_UI_THREAD

			for(std::vector<IUpdateableViewController*>::iterator it = m_updateTargetsUi.begin(); it != m_updateTargetsUi.end(); ++ it)
			{
				IUpdateableViewController& updatable =**it;
				updatable.UpdateUiThread(deltaSeconds);
			}
		}
	}
}
