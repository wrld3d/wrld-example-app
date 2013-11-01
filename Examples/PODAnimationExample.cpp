//
//  PODAnimationExample.cpp
//  ExampleApp
//
//  Created by Scott on 05/08/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#include "PODAnimationExample.h"
#include "ShaderCompiler.h"
#include <sys/time.h>

namespace Examples
{
    PODAnimationExample::PODAnimationExample(Eegeo::Rendering::RenderContext& renderContext,
                                             Eegeo::Helpers::IFileIO& fileIO,
                                             Eegeo::Helpers::ITextureFileLoader& textureLoader,
                                             Eegeo::Lighting::GlobalFogging& fogging)
    :renderContext(renderContext)
    ,fileIO(fileIO)
    ,textureLoader(textureLoader)
    ,pModel(NULL)
    ,globalFogging(fogging)
    {
        
    }
    
    void PODAnimationExample::Start()
    {
        pModel = new Eegeo::Model(renderContext.GetGLState(), textureLoader, fileIO);
        pModel->Load("Test_ROBOT_ARM.pod");
        Eegeo_ASSERT(pModel->GetRootNode());

    }
    
    void PODAnimationExample::Suspend()
    {
        delete pModel;
        pModel = NULL;
    }
    
    void PODAnimationExample::Update()
    {
        pModel->UpdateAnimator(1.0f/30.0f);
    }
    
    void PODAnimationExample::Draw()
    {
        //create basis around a known location off coast of SF
        Eegeo::m44 transform;
        Eegeo::dv3 location = Eegeo::dv3(4256955.9749164,3907407.6184668,-2700108.75541722);
        Eegeo::v3 up(location.Norm().ToSingle());
        Eegeo::v3 forward = (location  - Eegeo::v3(0.f, 1.f, 0.f)).Norm().ToSingle();
        Eegeo::v3 right(Eegeo::v3::Cross(up, forward).Norm());
        forward = Eegeo::v3::Cross(up, right);
        Eegeo::v3 cameraRelativePos = (location - renderContext.GetCameraOriginEcef()).ToSingle();
        Eegeo::m44 scaleMatrix;
        scaleMatrix.Scale(1.f);
        Eegeo::m44 cameraRelativeTransform;
        cameraRelativeTransform.SetFromBasis(right, up, forward, cameraRelativePos);
        Eegeo::m44::Mul(transform, cameraRelativeTransform, scaleMatrix);
        transform.SetRow(3, Eegeo::v4(cameraRelativePos, 1.f));
        
        renderContext.GetGLState().DepthTest.Enable();
        renderContext.GetGLState().DepthFunc(GL_LEQUAL);
        
        //loaded model faces are ccw
        renderContext.GetGLState().FrontFace(GL_CCW);
        
        pModel->GetRootNode()->SetVisible(true);
        pModel->GetRootNode()->SetLocalMatrix(transform);
        pModel->GetRootNode()->UpdateRecursive();
        pModel->GetRootNode()->UpdateSphereRecursive();
        pModel->GetRootNode()->DrawRecursive(renderContext, globalFogging, NULL, true, false);
       
        renderContext.GetGLState().FrontFace(GL_CW);

    }
}
