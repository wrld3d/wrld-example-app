// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SceneModelRenderableFilter.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace SdkModel
        {
            
            class IAnimatedSceneModel : Eegeo::NonCopyable
            {
            public:
                virtual ~IAnimatedSceneModel(){};
                
                virtual const Eegeo::dv3& GetEcefPosition() const = 0;
                virtual void SetEcefPosition(const Eegeo::dv3& ecefPosition) = 0;
                virtual void SetRootTransform(const Eegeo::m44& transform) = 0;
                virtual void AddToSceneRenderableFilter(Eegeo::Rendering::Filters::SceneModelRenderableFilter& renderableFilter) = 0;
                virtual void RemoveFromSceneRenderableFilter(Eegeo::Rendering::Filters::SceneModelRenderableFilter& renderableFilter) = 0;
                virtual void Play() = 0;
                virtual void Update(float dt) = 0;
                virtual void Stop() = 0;
            };
        }
    }
}
