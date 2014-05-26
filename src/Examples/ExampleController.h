//
//  ExampleController.h
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__ExampleController__
#define __ExampleApp__ExampleController__

#include "IExample.h"
#include "IExampleFactory.h"
#include "Types.h"
#include "EegeoWorld.h"
#include "UIActionHandler.h"
#include "IExampleControllerView.h"
#include <vector>
#include <string>

namespace Examples
{
    class ExampleController : private Eegeo::NonCopyable
    {
        IExample* m_pCurrentExample;
        int m_currentExampleFactoryIndex;
        Eegeo::EegeoWorld& m_world;
        std::vector<IExampleFactory*> m_factories;
        
        IExampleControllerView& m_view;
        UIActionHandler<ExampleController> m_nextExampleHandler;
        UIActionHandler<ExampleController> m_previousExampleHandler;
        UIActionHandler<ExampleController> m_selectedExampleChangedHandler;
        
        void DestroyCurrentExample();
        
        void RefreshExample();

    public:
        ExampleController(Eegeo::EegeoWorld& world,
                          IExampleControllerView& view);
        
        ~ExampleController();
        
        std::vector<std::string> GetExampleNames() const;

        void UpdateSelectedExample();

        void ActivatePrevious();
        
        void ActivateNext();
        
        void EarlyUpdate(float dt,
                         Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCamera,
                         Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController);
        
        void Update(float dt);
        
        void Draw();
        
        void RegisterExample(IExampleFactory* pFactory);
        
        template <typename TExampleFactory>
        void RegisterExample()
        {
            m_factories.push_back(Eegeo_NEW((TExampleFactory)(m_world)));
        }
        
        template <typename TExampleFactory>
        void RegisterCameraExample(Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCamera)
        {
            m_factories.push_back(Eegeo_NEW((TExampleFactory)(m_world, globeCamera)));
        }
        
        bool Event_TouchRotate(const AppInterface::RotateData& data);
        bool Event_TouchRotate_Start(const AppInterface::RotateData& data);
        bool Event_TouchRotate_End(const AppInterface::RotateData& data);
        
        bool Event_TouchPinch(const AppInterface::PinchData& data);
        bool Event_TouchPinch_Start(const AppInterface::PinchData& data);
        bool Event_TouchPinch_End(const AppInterface::PinchData& data);
        
        bool Event_TouchPan(const AppInterface::PanData& data);
        bool Event_TouchPan_Start(const AppInterface::PanData& data);
        bool Event_TouchPan_End(const AppInterface::PanData& data);
        
        bool Event_TouchTap(const AppInterface::TapData& data);
        bool Event_TouchDoubleTap(const AppInterface::TapData& data);
        
        bool Event_TouchDown(const AppInterface::TouchData& data);
        bool Event_TouchMove(const AppInterface::TouchData& data);
        bool Event_TouchUp(const AppInterface::TouchData& data);
    };
}

#endif /* defined(__ExampleApp__ExampleController__) */
