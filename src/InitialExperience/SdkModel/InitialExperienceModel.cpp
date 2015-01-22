// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "IInitialExperienceStep.h"
#include "InitialExperienceModel.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            InitialExperienceModel::InitialExperienceModel(const std::vector<IInitialExperienceStep*>& initialExperienceSteps)
                : m_currentStepIndex(0)
                , m_steps(initialExperienceSteps)
            {
            }

            InitialExperienceModel::~InitialExperienceModel()
            {
                for(std::vector<IInitialExperienceStep*>::iterator it = m_steps.begin(); it != m_steps.end(); ++ it)
                {
                    IInitialExperienceStep* pStep = *it;
                    Eegeo_DELETE pStep;
                }

                m_steps.clear();
            }

            bool InitialExperienceModel::HasCompletedInitialExperience() const
            {
                return m_currentStepIndex >= m_steps.size();
            }

            void InitialExperienceModel::DoNextPartOfInitialExperience()
            {
                Eegeo_ASSERT(!HasCompletedInitialExperience(), "No more steps in initial experience to do.\n");

                while(!HasCompletedInitialExperience())
                {
                    IInitialExperienceStep& step = GetCurrentStep();

                    if(!step.HasCompleted())
                    {
                        if(!step.HasStarted())
                        {
                            step.PerformInitialExperience();
                        }
                        break;
                    }

                    ++ m_currentStepIndex;
                }
            }

            void InitialExperienceModel::UpdateCurrentStep(float deltaSeconds)
            {
                Eegeo_ASSERT(!HasCompletedInitialExperience(), "Initial Experience is already complete.\n");

                IInitialExperienceStep& step = GetCurrentStep();

                step.Update(deltaSeconds);
            }

            IInitialExperienceStep& InitialExperienceModel::GetCurrentStep()
            {
                return *m_steps[m_currentStepIndex];
            }
        }
    }
}
