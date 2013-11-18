#ifndef __ExampleApp__DebugSphereExample__
#define __ExampleApp__DebugSphereExample__

#include "IExample.h"
#include "LatLongAltitude.h"
#include "Rendering.h"
#include "DebugRendering.h"

#include <vector>

namespace Examples
{
    class DebugSphereExample : public IExample
    {
    private:
        std::vector<Eegeo::DebugRendering::SphereMesh*> renderables;
        Eegeo::Rendering::RenderContext& renderContext;
        Eegeo::Space::LatLongAltitude interestLocation;
        
        void AddSphere(Eegeo::Space::LatLongAltitude sphereLocation,
                       Eegeo::v3 color);
        
    public:
        DebugSphereExample(Eegeo::Rendering::RenderContext& renderContext,
                           Eegeo::Space::LatLongAltitude interestLocation);
        
        void Start();
        void Update(float dt);
        void Draw();
        void Suspend();
    };
}


#endif /* defined(__ExampleApp__DebugSphereExample__) */
