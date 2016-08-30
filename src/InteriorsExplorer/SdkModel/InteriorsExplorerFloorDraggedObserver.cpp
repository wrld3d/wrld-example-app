// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerFloorDraggedObserver.h"
#include "InteriorsExplorerModel.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
           
            InteriorsExplorerFloorDraggedObserver::InteriorsExplorerFloorDraggedObserver(const std::shared_ptr<InteriorsExplorerModel>& interiorExplorerModel,
                                                                                         const std::shared_ptr<Eegeo::ITouchController>& interiorCameraTouchController)
            : m_interiorCameraTouchController(interiorCameraTouchController)
            , m_interiorExplorerModel(interiorExplorerModel)
            , m_floorDraggedCallback(this, &InteriorsExplorerFloorDraggedObserver::OnFloorDragged)
            {
                m_interiorExplorerModel->InsertInteriorExplorerFloorSelectionDraggedCallback(m_floorDraggedCallback);
            }
                
            InteriorsExplorerFloorDraggedObserver::~InteriorsExplorerFloorDraggedObserver()
            {
                m_interiorExplorerModel->RemoveInteriorExplorerFloorSelectionDraggedCallback(m_floorDraggedCallback);
            }
            
            void InteriorsExplorerFloorDraggedObserver::OnFloorDragged()
            {
                m_interiorCameraTouchController->Reset();
            }
        }
    }
}