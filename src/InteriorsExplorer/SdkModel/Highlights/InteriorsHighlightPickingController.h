// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "PickingController.h"
#include "Collision.h"
#include "Rendering.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                class InteriorsHighlightPickingController : public Eegeo::Picking::PickingController
                {
                public:
                    InteriorsHighlightPickingController(Eegeo::Collision::IRayCaster& rayCaster,
                                                        const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                        Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService);
                    
                    void ProcessRayCastResult(const Eegeo::Collision::RayCasterResult& pickResult);
                    
                private:

                };
            }
        }
    }
}