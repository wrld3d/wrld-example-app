// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IInitialExperienceStep.h"

namespace ExampleApp
{
namespace InitialExperience
{
namespace PreLoad
{
class IInitialExperiencePreLoadModel : public IInitialExperienceStep
{
public:
	virtual ~IInitialExperiencePreLoadModel() { }

	virtual void ShowOptions() = 0;
};
}
}
}
