// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "IInitialExperienceModel.h"
#include "InitialExperienceController.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            InitialExperienceController::InitialExperienceController(IInitialExperienceModel& initialExperienceModel)
                : m_initialExperienceModel(initialExperienceModel)
            {

            }

            InitialExperienceController::~InitialExperienceController()
            {

            }

            void InitialExperienceController::Update(float deltaSeconds)
            {
                if(!m_initialExperienceModel.HasCompletedInitialExperience())
                {
                    m_initialExperienceModel.DoNextPartOfInitialExperience();

                    if(!m_initialExperienceModel.HasCompletedInitialExperience())
                    {
                        m_initialExperienceModel.UpdateCurrentStep(deltaSeconds);
                    }
                }
            }
        }
    };
}
