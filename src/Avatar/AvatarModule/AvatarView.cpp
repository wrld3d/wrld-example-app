// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AvatarView.h"
#include "Types.h"

#include "EcefTangentBasis.h"
#include "SceneModel.h"
#include "SceneModelAnimator.h"
#include "SceneModelRenderableFilter.h"
#include "CameraHelpers.h"
#include "DebugRenderingModule.h"
#include "DebugRenderer.h"
#include "SpaceHelpers.h"
#include "IAvatarSceneModelFactory.h"
#include "Bounds.h"
#include "TransformMeshRenderableFilter.h"
#include "IndoorLocation.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace AvatarModule
        {
            AvatarView::AvatarView(SdkModel::IAnimatedSceneModel* pIdleAnimatedModel,
                                             SdkModel::IAnimatedSceneModel* pWalkAnimatedModel,
                                             Eegeo::Rendering::Filters::SceneModelRenderableFilter& sceneModelRenderableFilter,
                                             RenderingTransformMesh::SdkModel::TransformMeshRenderable* pAvatarShadow,
                                             RenderingTransformMesh::SdkModel::TransformMeshRenderableFilter& transformMeshRenderableFilter,
                                             Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule)
            : m_sceneModelRenderableFilter(sceneModelRenderableFilter)
            , m_transformMeshRenderableFilter(transformMeshRenderableFilter)
            , m_pIdleAnimatedModel(pIdleAnimatedModel)
            , m_pWalkAnimatedModel(pWalkAnimatedModel)
            , m_pAvatarShadow(pAvatarShadow)
            , m_isWalking(false)
            , m_floorHeightAboveSeaLevel(0)
            , m_heading(0.0f)
            , m_latLong(0.0f, 0.0f)
            , m_avatarHidden(false)
            {
                Eegeo_ASSERT(m_pIdleAnimatedModel != NULL, "AvatarView must have an Idle IAnimatedSceneModel");
                Eegeo_ASSERT(m_pWalkAnimatedModel != NULL, "AvatarView must have a Walk IAnimatedSceneModel");
                Eegeo_ASSERT(m_pAvatarShadow      != NULL, "AvatarView must have a Shadow");
                
                m_pIdleAnimatedModel->AddToSceneRenderableFilter(m_sceneModelRenderableFilter);
                m_transformMeshRenderableFilter.AddTransformMeshRenderable(*m_pAvatarShadow);
                
                Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(m_latLong.ToECEF(),
                                                                                  m_heading,
                                                                                  m_cameraInterestBasis);
                
                m_pIdleAnimatedModel->Play();
            }
            
            AvatarView::~AvatarView()
            {
                if(!m_avatarHidden)
                {
                    if(!m_isWalking)
                    {
                        m_pIdleAnimatedModel->RemoveFromSceneRenderableFilter(m_sceneModelRenderableFilter);
                    }
                    else
                    {
                        m_pWalkAnimatedModel->RemoveFromSceneRenderableFilter(m_sceneModelRenderableFilter);
                    }
                    m_transformMeshRenderableFilter.RemoveTransformMeshRenderable(*m_pAvatarShadow);
                }
            
                Eegeo_DELETE m_pIdleAnimatedModel;
                m_pIdleAnimatedModel = NULL;
                
                Eegeo_DELETE m_pWalkAnimatedModel;
                m_pWalkAnimatedModel = NULL;
                
                Eegeo_DELETE m_pAvatarShadow;
                m_pAvatarShadow = NULL;
            }
            
            void AvatarView::SetLatLongHeading(const Eegeo::Space::LatLong& latLong, const float headingDegrees)
            {
                m_latLong = latLong;
                m_heading = headingDegrees;
                
                Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(m_latLong.ToECEF(),
                                                                                  m_heading,
                                                                                  m_cameraInterestBasis);
                
                Eegeo::m33 basisOrientation;
                basisOrientation.SetFromBasis(-m_cameraInterestBasis.GetRight(), m_cameraInterestBasis.GetUp(), m_cameraInterestBasis.GetForward());
                
                
                const float scaleFactor = 8.0f;
                Eegeo::m44 scale;
                
                scale.Scale(scaleFactor);
                
                Eegeo::m44 scaledOrientationMatrix;
                Eegeo::m44::Mul(scaledOrientationMatrix, scale, basisOrientation.ToM44());
                
                // need to get the terrain height, for now just use a quick offset
                const Eegeo::v3 heightAboveSeaLevel = (m_cameraInterestBasis.GetUp() * m_floorHeightAboveSeaLevel);
                const Eegeo::v3 shadowHeightAboveSeaLevel = (m_cameraInterestBasis.GetUp() * (m_floorHeightAboveSeaLevel+0.5f));
                
                m_pIdleAnimatedModel->SetRootTransform(scaledOrientationMatrix);
                m_pIdleAnimatedModel->SetEcefPosition(m_cameraInterestBasis.GetPointEcef() + heightAboveSeaLevel);
                
                m_pWalkAnimatedModel->SetRootTransform(scaledOrientationMatrix);
                m_pWalkAnimatedModel->SetEcefPosition(m_cameraInterestBasis.GetPointEcef() + heightAboveSeaLevel);
                
                m_pAvatarShadow->SetTransform(scaledOrientationMatrix);
                m_pAvatarShadow->SetEcefPosition(m_cameraInterestBasis.GetPointEcef() + shadowHeightAboveSeaLevel);
            }
            
            void AvatarView::SetHeightAboveSeaLevel(float heightAboveSeaLevel)
            {
                if(m_floorHeightAboveSeaLevel != heightAboveSeaLevel)
                {
                    m_floorHeightAboveSeaLevel = heightAboveSeaLevel;
                    SetLatLongHeading(m_latLong, m_heading);
                }
            }
            
            void AvatarView::StartMoving()
            {
                if(m_isWalking || m_avatarHidden)
                {
                    return;
                }
                m_isWalking = true;
                m_pIdleAnimatedModel->RemoveFromSceneRenderableFilter(m_sceneModelRenderableFilter);
                m_pWalkAnimatedModel->AddToSceneRenderableFilter(m_sceneModelRenderableFilter);
                
                m_pIdleAnimatedModel->Stop();
                m_pWalkAnimatedModel->Play();
            }
            
            void AvatarView::StopMoving()
            {
                if(!m_isWalking || m_avatarHidden)
                {
                    return;
                }
                
                m_isWalking = false;
                m_pWalkAnimatedModel->RemoveFromSceneRenderableFilter(m_sceneModelRenderableFilter);
                m_pIdleAnimatedModel->AddToSceneRenderableFilter(m_sceneModelRenderableFilter);
                
                m_pIdleAnimatedModel->Play();
                m_pWalkAnimatedModel->Stop();
            }
            
            void AvatarView::HideAvatar()
            {
                if(!m_isWalking)
                {
                    m_pIdleAnimatedModel->RemoveFromSceneRenderableFilter(m_sceneModelRenderableFilter);
                    m_pIdleAnimatedModel->Stop();
                }
                else
                {
                    m_pWalkAnimatedModel->RemoveFromSceneRenderableFilter(m_sceneModelRenderableFilter);
                    m_pWalkAnimatedModel->Stop();
                }
                m_transformMeshRenderableFilter.RemoveTransformMeshRenderable(*m_pAvatarShadow);
                
                m_avatarHidden = true;
            }
            
            void AvatarView::ShowAvatar()
            {
                if(!m_isWalking)
                {
                    m_pIdleAnimatedModel->AddToSceneRenderableFilter(m_sceneModelRenderableFilter);
                    m_pIdleAnimatedModel->Play();
                }
                else
                {
                    m_pWalkAnimatedModel->AddToSceneRenderableFilter(m_sceneModelRenderableFilter);
                    m_pWalkAnimatedModel->Play();
                }
                m_transformMeshRenderableFilter.AddTransformMeshRenderable(*m_pAvatarShadow);
                
                m_avatarHidden = false;
            }
            
            bool AvatarView::IsShowingAvatar()
            {
                return !m_avatarHidden;
            }
            
            void AvatarView::Update(float dt)
            {
                m_pIdleAnimatedModel->Update(dt);
                m_pWalkAnimatedModel->Update(dt);
            }
        }
    }
}