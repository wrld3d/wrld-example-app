// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "IWorldPinSelectionHandler.h"
#include "InteriorController.h"
#include "InteriorsExplorerCameraController.h"
#include "InteriorMarkerModel.h"

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
                                                 Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                 InteriorsExplorerCameraController& cameraController,
                                                 const Eegeo::dv3& ecefInterestPoint)
                : m_interiorId(interiorId)
                , m_interiorController(interiorController)
                , m_cameraController(cameraController)
                , m_ecefInterestPoint(ecefInterestPoint)
                {
                    
                }
                
                void SelectPin()
                {
                    m_interiorController.SetSelectedInterior(m_interiorId);
                    
                    const float defaultDistance = 300.0f;
                    m_cameraController.SetInterestLocation(m_ecefInterestPoint);
                    m_cameraController.SetDistanceToInterest(defaultDistance);
                }
                
            private:
                
                Eegeo::Resources::Interiors::InteriorId m_interiorId;
                Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                InteriorsExplorerCameraController& m_cameraController;
                const Eegeo::dv3 m_ecefInterestPoint;
            };
        }
    }
}