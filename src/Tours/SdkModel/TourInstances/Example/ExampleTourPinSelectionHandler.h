// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinSelectionHandler.h"
#include "TourModel.h"
#include "Tours.h"
#include "ITourService.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace Example
                {
                    class ExampleTourPinSelectionHandler : public WorldPins::SdkModel::IWorldPinSelectionHandler
                    {
                        
                    public:
                        ExampleTourPinSelectionHandler()
                        { }
                        
                        void SelectPin()
                        {
                            Eegeo_TTY("Selected");
                        }
                    };
                }
            }
        }
    }
}
