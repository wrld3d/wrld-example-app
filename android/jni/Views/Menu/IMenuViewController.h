// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IUpdateableViewController.h"

namespace ExampleApp
{
namespace Menu
{
class IMenuViewController : public ViewControllerUpdater::IUpdateableViewController
{
public:
	virtual ~IMenuViewController() { }
};
}
}
