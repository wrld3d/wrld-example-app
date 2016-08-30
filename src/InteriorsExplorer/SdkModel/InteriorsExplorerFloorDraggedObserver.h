// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "InteriorsExplorer.h"
#include "ITouchController.h"
#include "Types.h"
#include "ICallback.h"
#include <memory>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsExplorerFloorDraggedObserver : protected Eegeo::NonCopyable
            {
            public:
                
                InteriorsExplorerFloorDraggedObserver(const std::shared_ptr<InteriorsExplorerModel>& interiorExplorerModel,
                                                      const std::shared_ptr<Eegeo::ITouchController>& interiorCameraTouchController);
                
                ~InteriorsExplorerFloorDraggedObserver();
                
            private:
                
                void OnFloorDragged();
                
                const std::shared_ptr<InteriorsExplorerModel> m_interiorExplorerModel;
                const std::shared_ptr<Eegeo::ITouchController> m_interiorCameraTouchController;
                Eegeo::Helpers::TCallback0<InteriorsExplorerFloorDraggedObserver> m_floorDraggedCallback;
            };
        }
    }
}