// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ExitCurrentInteriorStage.h"
#include "IAppModeModel.h"
#include "InteriorsExplorerModel.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            ExitCurrentInteriorStage::ExitCurrentInteriorStage(InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                               AppModes::SdkModel::IAppModeModel& appModeModel)
            : m_appModeModel(appModeModel)
            , m_interiorsExplorerModel(interiorsExplorerModel)
            {
            }
            
            void ExitCurrentInteriorStage::Start()
            {
                m_interiorsExplorerModel.Exit();
            }
            
            void ExitCurrentInteriorStage::Update(float dt)
            {
            }
            
            void ExitCurrentInteriorStage::End()
            {
            }
            
            const bool ExitCurrentInteriorStage::StageIsComplete() const
            {
                return m_appModeModel.GetAppMode() == AppModes::SdkModel::WorldMode;
            }
            
            const bool ExitCurrentInteriorStage::StageHasFailed() const
            {
                return false;
            }
        }
    }
}