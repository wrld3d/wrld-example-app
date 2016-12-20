// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorSelectionController.h"
#include "InteriorSelectionModel.h"
#include "InteriorMarkerModelRepository.h"
#include "InteriorsCameraController.h"
#include "InteriorMarkerModel.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorSelectionController::InteriorSelectionController(
                                                                     Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                     const Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& interiorMarkerModelRepository,
                                                                     Eegeo::Resources::Interiors::InteriorsCameraController& cameraController)
            : m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorMarkerModelRepository(interiorMarkerModelRepository)
            , m_cameraController(cameraController)
            , m_interiorSelectionChangedHandler(this, &InteriorSelectionController::OnInteriorSelectionChanged)
            {
                m_interiorSelectionModel.RegisterSelectionChangedCallback(m_interiorSelectionChangedHandler);
            }
            
            InteriorSelectionController::~InteriorSelectionController()
            {
                m_interiorSelectionModel.UnregisterSelectionChangedCallback(m_interiorSelectionChangedHandler);
            }
            
            
            void InteriorSelectionController::OnInteriorSelectionChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                if (m_interiorSelectionModel.IsInteriorSelected())
                {
                    OnInteriorSelected(interiorId);
                }
            }
            
            void InteriorSelectionController::OnInteriorSelected(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                if (!m_interiorMarkerModelRepository.Contains(interiorId))
                {
                    return;
                }
                
                const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel& interiorMarkerModel = m_interiorMarkerModelRepository.Get(interiorId);
                
                const Eegeo::dv3& ecefInterestPoint = interiorMarkerModel.GetMarkerLatLongAltitude().ToECEF();

                m_cameraController.SetInterestLocation(ecefInterestPoint);
                m_cameraController.SetDistanceToInterest(InteriorsExplorer::DefaultInteriorTransitionInterestDistance);
            }
            
            
            

                

        }
    }
}