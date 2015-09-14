// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInteriorsExplorerInputDelegate.h"
#include "Types.h"
#include "Interiors.h"
#include "AppInterface.h"
#include "GlobeCamera.h"
#include "BidirectionalBus.h"
#include "MenuDragStateChangedMessage.h"
#include "ICallback.h"

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
                                               const Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController,
                                               ExampleAppMessaging::TMessageBus& messageBus);

                bool HandleTouchTap(const AppInterface::TapData& tapData);

            private:
                bool m_menuIsDragging;
                
                Eegeo::Resources::Interiors::InteriorsController& m_interiorsController;
                Eegeo::Resources::Interiors::InteriorsPinsController& m_interiorsPinsController;
                const Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_globeCameraController;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                void OnMenuDragStateChanged(const Menu::MenuDragStateChangedMessage& message);
                Eegeo::Helpers::TCallback1<InteriorsExplorerInputDelegate, const Menu::MenuDragStateChangedMessage&> m_menuDragStateChangedHandler;
            };
        }
    }
}