// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "ViewControllerUpdater.h"
#include "IViewControllerUpdaterModule.h"

namespace ExampleApp
{
namespace ViewControllerUpdater
{
class ViewControllerUpdaterModule: public IViewControllerUpdaterModule, private Eegeo::NonCopyable
{
private:
	IViewControllerUpdaterModel* m_pViewControllerUpdaterModel;

public:
	ViewControllerUpdaterModule();

	~ViewControllerUpdaterModule();

	IViewControllerUpdaterModel& GetViewControllerUpdaterModel() const;
};
}
}
