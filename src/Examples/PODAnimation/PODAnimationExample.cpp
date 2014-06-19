// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PODAnimationExample.h"
#include "ShaderCompiler.h"
#include "CameraHelpers.h"
#include <sys/time.h>

namespace Examples
{
PODAnimationExample::PODAnimationExample(Eegeo::Rendering::RenderContext& renderContext,
        Eegeo::Helpers::IFileIO& fileIO,
        Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
        Eegeo::Lighting::GlobalFogging& fogging,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController)
	:m_renderContext(renderContext)
	,m_fileIO(fileIO)
	,m_textureRequestor(textureRequestor)
	,m_pModel(NULL)
	,m_globalFogging(fogging)
	,m_globeCameraStateRestorer(cameraController)
{
	Eegeo::Space::EcefTangentBasis cameraInterestBasis;

	Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
	    Eegeo::Space::LatLong::FromDegrees(37.780642, -122.385876).ToECEF(),
	    16.472872,
	    cameraInterestBasis);

	cameraController.SetView(cameraInterestBasis, 1209.007812);
}

void PODAnimationExample::Start()
{
	m_pModel = Eegeo::Model::CreateFromPODFile("pod_animation_example/Test_ROBOT_ARM.pod", m_fileIO, m_renderContext.GetGLState(), &m_textureRequestor, "pod_animation_example/");
	Eegeo_ASSERT(m_pModel->GetRootNode());

}

void PODAnimationExample::Suspend()
{
	delete m_pModel;
	m_pModel = NULL;
}

void PODAnimationExample::Update(float dt)
{
	m_pModel->UpdateAnimator(1.0f/30.0f);
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
	Eegeo::v3 cameraRelativePos = (location - m_renderContext.GetCameraOriginEcef()).ToSingle();
	Eegeo::m44 scaleMatrix;
	scaleMatrix.Scale(1.f);
	Eegeo::m44 cameraRelativeTransform;
	cameraRelativeTransform.SetFromBasis(right, up, forward, cameraRelativePos);
	Eegeo::m44::Mul(transform, cameraRelativeTransform, scaleMatrix);
	transform.SetRow(3, Eegeo::v4(cameraRelativePos, 1.f));

	m_renderContext.GetGLState().DepthTest.Enable();
	m_renderContext.GetGLState().DepthFunc(GL_LEQUAL);

	//loaded model faces are ccw
	m_renderContext.GetGLState().FrontFace(GL_CCW);

	m_pModel->GetRootNode()->SetVisible(true);
	m_pModel->GetRootNode()->SetLocalMatrix(transform);
	m_pModel->GetRootNode()->UpdateRecursive();
	m_pModel->GetRootNode()->UpdateSphereRecursive();
	m_pModel->GetRootNode()->DrawRecursive(m_renderContext, m_globalFogging, NULL, true, false);

	m_renderContext.GetGLState().FrontFace(GL_CW);

}
}
