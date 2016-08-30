// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "InteriorsExplorer.h"
#include "IWorldPinSelectionHandler.h"
#include "InteriorSelectionModel.h"
#include "InteriorMarkerModel.h"
#include "InteriorWorldPinController.h"
#include "IInteriorCameraController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorWorldPinSelectionHandler : public WorldPins::SdkModel::IWorldPinSelectionHandler
            {
            public:
                
                InteriorWorldPinSelectionHandler(const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                 Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                 IInteriorCameraController& cameraController,
                                                 const Eegeo::dv3& ecefInterestPoint,
                                                 const InteriorWorldPinController& pinController)
                : m_interiorId(interiorId)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_cameraController(cameraController)
                , m_ecefInterestPoint(ecefInterestPoint)
                , m_pinController(pinController)
                {
                    
                }
                
                void SelectPin()
                {
                    if(!m_pinController.PinInteractionAllowed(m_interiorId.Value()))
                    {
                        return;
                    }
                    
                    m_interiorSelectionModel.SelectInteriorId(m_interiorId);
                    
                    m_cameraController.SetInterestLocation(m_ecefInterestPoint);
                    m_cameraController.SetDistanceToInterest(InteriorsExplorer::DefaultInteriorTransitionInterestDistance);
                }
                
            private:
                
                Eegeo::Resources::Interiors::InteriorId m_interiorId;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                IInteriorCameraController& m_cameraController;
                const Eegeo::dv3 m_ecefInterestPoint;
                const InteriorWorldPinController& m_pinController;
            };
        }
    }
}