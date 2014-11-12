// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace ExampleApp
{
namespace InitialExperience
{
class IInitialExperienceController
{
public:
	virtual ~IInitialExperienceController() { }

	virtual void Update(float deltaSeconds) = 0;
};
}
}
