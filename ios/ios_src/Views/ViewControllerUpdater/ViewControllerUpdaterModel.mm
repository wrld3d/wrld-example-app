// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <algorithm>
#include "ViewControllerUpdaterModel.h"
#include "UpdateProtocol.h"

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

		void ViewControllerUpdaterModel::AddUpdateableObject(id<UpdateProtocol> updateProtocolImplementation)
		{
			m_updateTargets.push_back(updateProtocolImplementation);
		}

		void ViewControllerUpdaterModel::RemoveUpdateableObject(id<UpdateProtocol> updateProtocolImplementation)
		{
			m_updateTargets.erase(std::remove(m_updateTargets.begin(), m_updateTargets.end(), &updateProtocolImplementation), m_updateTargets.end());
		}

		void ViewControllerUpdaterModel::UpdateObjects(float deltaSeconds)
		{
			for(std::vector<id<UpdateProtocol> >::iterator it = m_updateTargets.begin(); it != m_updateTargets.end(); ++ it)
			{
				id<UpdateProtocol> pUpdatable = *it;
				[pUpdatable update:deltaSeconds];
			}
		}
	}
}
