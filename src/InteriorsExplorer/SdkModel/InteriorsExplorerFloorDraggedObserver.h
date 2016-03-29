// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "InteriorsExplorer.h"
#include "ITouchController.h"
#include "Types.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsExplorerFloorDraggedObserver : protected Eegeo::NonCopyable
            {
            public:
                
                InteriorsExplorerFloorDraggedObserver(InteriorsExplorerModel& interiorExplorerModel,
                                                      Eegeo::ITouchController& interiorCameraTouchController);
                
                ~InteriorsExplorerFloorDraggedObserver();
                
            private:
                
                void OnFloorDragged();
                
                InteriorsExplorerModel& m_interiorExplorerModel;
                Eegeo::ITouchController& m_interiorCameraTouchController;
                Eegeo::Helpers::TCallback0<InteriorsExplorerFloorDraggedObserver> m_floorDraggedCallback;
            };
        }
    }
}