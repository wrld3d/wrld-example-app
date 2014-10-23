// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "IInitialExperienceModel.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        class InitialExperienceModel : public IInitialExperienceModel, private Eegeo::NonCopyable
        {
            size_t m_currentStepIndex;
            std::vector<IInitialExperienceStep*> m_steps;
            
        public:
            InitialExperienceModel(const std::vector<IInitialExperienceStep*>& initialExperienceSteps);
            
            ~InitialExperienceModel();
            
            bool HasCompletedInitialExperience() const;
            
            void DoNextPartOfInitialExperience();
            
            void UpdateCurrentStep(float deltaSeconds);
            
        private:
            IInitialExperienceStep& GetCurrentStep();

        };
    }
}
