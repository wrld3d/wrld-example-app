#ifndef __ExampleApp__Example__
#define __ExampleApp__Example__

#include "IAppOnMap.h"

namespace Examples
{
    class IExample
    {
    public:
        virtual ~IExample() { }
        
        virtual void Start() = 0;
        virtual void EarlyUpdate(float dt) { }
        virtual void AfterCameraUpdate() { }
        virtual void Update(float dt) = 0;
        virtual void Draw() = 0;
        virtual void Suspend()= 0 ;
        
        virtual bool Event_TouchRotate 			(const AppInterface::RotateData& data) { return false; }
        virtual bool Event_TouchRotate_Start	(const AppInterface::RotateData& data) { return false; }
        virtual bool Event_TouchRotate_End 		(const AppInterface::RotateData& data) { return false; }
        
        virtual bool Event_TouchPinch 			(const AppInterface::PinchData& data) { return false; }
        virtual bool Event_TouchPinch_Start 	(const AppInterface::PinchData& data) { return false; }
        virtual bool Event_TouchPinch_End 		(const AppInterface::PinchData& data) { return false; }
        
        virtual bool Event_TouchPan				(const AppInterface::PanData& data) { return false; }
        virtual bool Event_TouchPan_Start		(const AppInterface::PanData& data) { return false; }
        virtual bool Event_TouchPan_End 		(const AppInterface::PanData& data) { return false; }
        
        virtual bool Event_TouchTap 			(const AppInterface::TapData& data) { return false; }
        virtual bool Event_TouchDoubleTap		(const AppInterface::TapData& data) { return false; }
        
        virtual bool Event_TouchDown 			(const AppInterface::TouchData& data) { return false; }
        virtual bool Event_TouchMove 			(const AppInterface::TouchData& data) { return false; }
        virtual bool Event_TouchUp 				(const AppInterface::TouchData& data) { return false; }
    };
}

#endif /* defined(__ExampleApp__Example__) */
