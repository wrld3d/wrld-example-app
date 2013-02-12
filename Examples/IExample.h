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
        virtual void Update() = 0;
        virtual void Draw() = 0;
        virtual void Suspend()= 0 ;
    };
}

#endif /* defined(__ExampleApp__Example__) */
