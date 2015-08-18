// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorsStreamingController.h"
#include "InteriorSelectionController.h"
#include "CameraFrustumStreamingVolume.h"


namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorsStreamingController::InteriorsStreamingController(Eegeo::Resources::Interiors::InteriorSelectionController& interiorSelectionController,
                                                                       Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume)
            : m_interiorSelectionController(interiorSelectionController)
            , m_cameraFrustumStreamingVolume(cameraFrustumStreamingVolume)
            , m_interiorStreamingBeginCallback(this, &InteriorsStreamingController::OnInteriorStreamingBegin)
            , m_interiorStreamingEndCallback(this, &InteriorsStreamingController::OnInteriorStreamingEnd)
            {
                m_interiorSelectionController.RegisterStreamingBeginCallback(m_interiorStreamingBeginCallback);
                m_interiorSelectionController.RegisterStreamingEndCallback(m_interiorStreamingEndCallback);
            }

            InteriorsStreamingController::~InteriorsStreamingController()
            {
                m_interiorSelectionController.UnregisterStreamingBeginCallback(m_interiorStreamingBeginCallback);
                m_interiorSelectionController.UnregisterStreamingEndCallback(m_interiorStreamingEndCallback);
            }

            void InteriorsStreamingController::OnInteriorStreamingBegin()
            {
                m_cameraFrustumStreamingVolume.SetForceMaximumRefinement(true);
            }
            
            void InteriorsStreamingController::OnInteriorStreamingEnd()
            {
                m_cameraFrustumStreamingVolume.SetForceMaximumRefinement(false);
            }
        }
    }
}