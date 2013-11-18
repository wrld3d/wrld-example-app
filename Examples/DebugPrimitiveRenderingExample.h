#ifndef __ExampleApp__DebugPrimitiveRenderingExample__
#define __ExampleApp__DebugPrimitiveRenderingExample__

#include "IExample.h"

namespace Eegeo
{
    namespace DebugRendering
    {
        class DebugPrimitiveRenderer;
    }
}

namespace Examples
{
    class DebugPrimitiveRenderingExample : public Examples::IExample
    {
    private:
        Eegeo::DebugRendering::DebugPrimitiveRenderer& m_debugPrimitiveRenderer;
    public:
        DebugPrimitiveRenderingExample(Eegeo::DebugRendering::DebugPrimitiveRenderer &debugPrimitiveRenderer) :
        m_debugPrimitiveRenderer(debugPrimitiveRenderer) {}
        
        void Start();
        void Update(float dt);
        void Draw();
        void Suspend();
    };
}


#endif /* defined(__ExampleApp__DebugPrimitiveRenderingExample__) */
