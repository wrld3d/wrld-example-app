// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "IViewControllerUpdaterModel.h"
#include "ViewControllerUpdater.h"

namespace ExampleApp
{
namespace ViewControllerUpdater
{
class ViewControllerUpdaterModel: public IViewControllerUpdaterModel, private Eegeo::NonCopyable
{
private:
	std::vector<id<UpdateProtocol> > m_updateTargets;

public:
	ViewControllerUpdaterModel();

	~ViewControllerUpdaterModel();

	void AddUpdateableObject(id<UpdateProtocol> updateProtocolImplementation);

	void RemoveUpdateableObject(id<UpdateProtocol> updateProtocolImplementation);

	void UpdateObjects(float deltaSeconds);
};
}
}

