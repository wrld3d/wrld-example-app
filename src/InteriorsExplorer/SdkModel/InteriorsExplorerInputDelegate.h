// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInteriorsExplorerInputDelegate.h"
#include "Types.h"
#include "Interiors.h"
#include "AppInterface.h"
#include "GlobeCamera.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsExplorerInputDelegate : public IInteriorsExplorerInputDelegate, private Eegeo::NonCopyable
            {
            public:
                InteriorsExplorerInputDelegate(Eegeo::Resources::Interiors::InteriorsController& interiorsController,
                                               Eegeo::Resources::Interiors::InteriorsPinsController& interiorsPinsController,
                                               Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController);

                bool HandleTouchTap(const AppInterface::TapData& tapData);

            private:
                Eegeo::Resources::Interiors::InteriorsController& m_interiorsController;
                Eegeo::Resources::Interiors::InteriorsPinsController& m_interiorsPinsController;
                Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_globeCameraController;
            };
        }
    }
}