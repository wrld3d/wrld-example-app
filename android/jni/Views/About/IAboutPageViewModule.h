// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AboutPageViewIncludes.h"

namespace ExampleApp
{
namespace AboutPage
{
class IAboutPageViewModule
{
public:
	virtual ~IAboutPageViewModule() { }

	virtual IAboutPageViewController& GetAboutPageViewController() const = 0;
};
}
}
