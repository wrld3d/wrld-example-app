// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace ExampleApp
{
namespace ViewControllerUpdater
{
class IUpdateableViewController
{
public:
	virtual ~IUpdateableViewController() { }

	virtual void UpdateUiThread(float deltaSeconds) = 0;
};
}
}
