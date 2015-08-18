// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"
#include "Streaming.h"
#include "ICallback.h"


namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsStreamingController : private Eegeo::NonCopyable
            {
            public:
                InteriorsStreamingController(Eegeo::Resources::Interiors::InteriorSelectionController& interiorSelectionController,
                                             Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume);
                
                ~InteriorsStreamingController();
                
            private:
                void OnInteriorStreamingBegin();
                void OnInteriorStreamingEnd();
            
                Eegeo::Resources::Interiors::InteriorSelectionController& m_interiorSelectionController;
                Eegeo::Streaming::CameraFrustumStreamingVolume& m_cameraFrustumStreamingVolume;
                
                Eegeo::Helpers::TCallback0<InteriorsStreamingController> m_interiorStreamingBeginCallback;
                Eegeo::Helpers::TCallback0<InteriorsStreamingController> m_interiorStreamingEndCallback;
            };
        }
    }
}