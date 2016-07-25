// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IAnimatedSceneModel.h"

#include "SceneModel.h"
#include "SceneModelAnimator.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace SdkModel
        {
            
            class XrayAnimatedSceneModel : public IAnimatedSceneModel
            {
            private:
                Eegeo::Rendering::SceneModels::SceneModel* m_pModel;
                Eegeo::Rendering::SceneModels::SceneModelAnimator* m_pAnimator;
                
            public:
                /// Constructor takes ownership of models and animators
                XrayAnimatedSceneModel(Eegeo::Rendering::SceneModels::SceneModel* pModel,
                                       Eegeo::Rendering::SceneModels::SceneModelAnimator* pAnimator);
                ~XrayAnimatedSceneModel();
                
                const Eegeo::dv3& GetEcefPosition() const;
                void SetEcefPosition(const Eegeo::dv3& ecefPosition);
                void SetRootTransform(const Eegeo::m44& transform);
                void AddToSceneRenderableFilter(Eegeo::Rendering::Filters::SceneModelRenderableFilter& renderableFilter);
                void RemoveFromSceneRenderableFilter(Eegeo::Rendering::Filters::SceneModelRenderableFilter& renderableFilter);
                void Play();
                void Update(float dt);
                void Stop();
            };
        }
    }
}
