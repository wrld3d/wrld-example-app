// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Avatar.h"
#include "IAvatarView.h"
#include "LatLongAltitude.h"

#include "IAnimatedSceneModel.h"
#include "Rendering.h"
#include "EcefTangentBasis.h"
#include "Modules.h"
#include "Interiors.h"
#include "RenderingTransformMesh.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace AvatarModule
        {
            class AvatarView : public SdkModel::IAvatarView
            {
            public:
                AvatarView(SdkModel::IAnimatedSceneModel* pIdleAnimatedModel,
                                SdkModel::IAnimatedSceneModel* pWalkAnimatedModel,
                                Eegeo::Rendering::Filters::SceneModelRenderableFilter& sceneModelRenderableFilter,
                                RenderingTransformMesh::SdkModel::TransformMeshRenderable* pAvatarShadow,
                                RenderingTransformMesh::SdkModel::TransformMeshRenderableFilter& transformMeshRenderableFilter,
                                Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule);
                
                ~AvatarView();
                
                void SetLatLongHeading(const Eegeo::Space::LatLong& latLong, const float headingDegrees);
                
                void SetHeightAboveSeaLevel(float heightAboveSeaLevel);
                
                void StartMoving();
                
                void StopMoving();
                
                void HideAvatar();
                
                void ShowAvatar();
                
                bool IsShowingAvatar();
                
                void Update(float dt);
                
            private:
                
                SdkModel::IAnimatedSceneModel* m_pIdleAnimatedModel;
                SdkModel::IAnimatedSceneModel* m_pWalkAnimatedModel;
                RenderingTransformMesh::SdkModel::TransformMeshRenderable* m_pAvatarShadow;
                
                bool m_isWalking;
                
                Eegeo::Rendering::Filters::SceneModelRenderableFilter& m_sceneModelRenderableFilter;
                RenderingTransformMesh::SdkModel::TransformMeshRenderableFilter& m_transformMeshRenderableFilter;
                
                float m_floorHeightAboveSeaLevel;
                float m_heading;
                Eegeo::Space::LatLong m_latLong;
                Eegeo::Space::EcefTangentBasis m_cameraInterestBasis;
                bool m_avatarHidden;
            };
        }
    }
}
