// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


namespace ExampleApp
{
    namespace PathDrawing
    {
        class IPathDrawingController
        {
        public:
            
            virtual ~IPathDrawingController() {}
            
            virtual void Update(float dt){};
            
        };
    }
}
