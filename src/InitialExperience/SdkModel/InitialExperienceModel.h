// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "IInitialExperienceModel.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            class InitialExperienceModel : public IInitialExperienceModel, private Eegeo::NonCopyable
            {
                size_t m_currentStepIndex;
                std::vector<IInitialExperienceStep*> m_steps;
                bool m_started;
                int m_lastLockedCameraStep;

            public:
                InitialExperienceModel(const std::vector<IInitialExperienceStep*>& initialExperienceSteps, int lastCameraLockedStep);

                ~InitialExperienceModel();

                bool HasCompletedInitialExperience() const;
                bool HasStartedInitialExperience() const;
                bool HasCompletedCurrentStep() const;

                void DoNextPartOfInitialExperience();

                void UpdateCurrentStep(float deltaSeconds);
                
                bool LockedCameraStepsCompleted() const;

            private:
                IInitialExperienceStep& GetCurrentStep();

            };
        }
    }
}
