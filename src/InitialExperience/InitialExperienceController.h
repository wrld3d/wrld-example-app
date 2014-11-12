// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "InitialExperience.h"
#include "IInitialExperienceController.h"

namespace ExampleApp
{
namespace InitialExperience
{
class InitialExperienceController : public IInitialExperienceController, private Eegeo::NonCopyable
{
	IInitialExperienceModel& m_initialExperienceModel;

public:
	InitialExperienceController(IInitialExperienceModel& initialExperienceModel);

	~InitialExperienceController();

	void Update(float deltaSeconds);
};
}
}
