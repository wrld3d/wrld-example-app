// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICameraTransitionStage.h"
#include "InteriorsExplorer.h"
#include "AppModes.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            class ExitCurrentInteriorStage : public ICameraTransitionStage
            {
            public:
                
                ExitCurrentInteriorStage(InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                         AppModes::SdkModel::IAppModeModel& appModeModel);
                
                void Start();
                void Update(float dt);
                void End();
                const bool StageIsComplete() const;
                const bool StageHasFailed() const;
                
            private:
                
                InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                AppModes::SdkModel::IAppModeModel& m_appModeModel;
            };
        }
    }
}