//
//  XrayAnimatedSceneModel.cpp
// 
//
//  Created by Francisco Mendonca on 17/09/2015.
//  Copyright (c) 2015 eeGeo. All rights reserved.
//

#include "XrayAnimatedSceneModel.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace SdkModel
        {
            
            XrayAnimatedSceneModel::XrayAnimatedSceneModel(Eegeo::Rendering::SceneModels::SceneModel* pModel,
                                                           Eegeo::Rendering::SceneModels::SceneModelAnimator* pAnimator)
            : m_pModel(pModel)
            , m_pAnimator(pAnimator)
            {
                Eegeo_ASSERT(m_pModel!=NULL && m_pAnimator!=NULL, "All models and animators need to be passed in");
            }
            
            XrayAnimatedSceneModel::~XrayAnimatedSceneModel()
            {
                Eegeo_DELETE(m_pModel);
                Eegeo_DELETE(m_pAnimator);
            }
            
            const Eegeo::dv3& XrayAnimatedSceneModel::GetEcefPosition() const
            {
                Eegeo::dv3 position = m_pModel->GetEcefPosition();                
                return m_pModel->GetEcefPosition();
            }
            
            void XrayAnimatedSceneModel::SetEcefPosition(const Eegeo::dv3& ecefPosition)
            {
                m_pModel->SetEcefPosition(ecefPosition);
            }
            
            void XrayAnimatedSceneModel::SetRootTransform(const Eegeo::m44& transform)
            {
                m_pModel->GetRootNode().SetTransform(transform);
            }
            
            void XrayAnimatedSceneModel::AddToSceneRenderableFilter(Eegeo::Rendering::Filters::SceneModelRenderableFilter& renderableFilter)
            {
                renderableFilter.AddSceneModel(*m_pModel);
            }
            
            void XrayAnimatedSceneModel::RemoveFromSceneRenderableFilter(Eegeo::Rendering::Filters::SceneModelRenderableFilter& renderableFilter)
            {
                renderableFilter.RemoveSceneModel(*m_pModel);
            }
            
            void XrayAnimatedSceneModel::Play()
            {
                m_pAnimator->Play();
            }
            
            void XrayAnimatedSceneModel::Update(float dt)
            {
                m_pAnimator->Update(dt);
            }
            
            void XrayAnimatedSceneModel::Stop()
            {
                m_pAnimator->Stop();
            }
        }
    }
}
