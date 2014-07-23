// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__CameraSplineExampleFactory__
#define __ExampleApp__CameraSplineExampleFactory__

#include "IExampleFactory.h"
#include "Camera.h"

namespace Examples
{
    class CameraSplineExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;
        
    public:
        CameraSplineExampleFactory(Eegeo::EegeoWorld& world,
                                   Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);
        
        std::string ExampleName() const;
        
        IExample* CreateExample() const;
    };
}


#endif /* defined(__ExampleApp__CameraSplineExampleFactory__) */
