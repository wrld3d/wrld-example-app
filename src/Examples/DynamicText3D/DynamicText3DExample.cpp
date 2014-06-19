// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DynamicText3DExample.h"
#include "UnicodeConverter.h"
#include "LatLongAltitude.h"
#include "RenderCamera.h"
#include "CubeMapCellInfo.h"
#include "CubeMap.h"
#include "CameraHelpers.h"

using namespace Eegeo;
using namespace Eegeo::Resources::PlaceNames;

namespace Examples
{
DynamicText3DExample::DynamicText3DExample(Eegeo::Rendering::GLState& glState,
        Eegeo::Camera::ICameraProvider& cameraProvider,
        Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
        Eegeo::Resources::PlaceNames::PlaceNameViewBuilder& placeNameViewBuilder,
        Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_glState(glState)
	, m_cameraProvider(cameraProvider)
	, m_environmentFlatteningService(environmentFlatteningService)
	, m_placeNameViewBuilder(placeNameViewBuilder)
	, m_world(world)
	, m_initialised(false)
	, m_globeCameraStateRestorer(globeCameraController)
{
	Eegeo::Space::EcefTangentBasis cameraInterestBasis;

	Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
	    Eegeo::Space::LatLong::FromDegrees(37.794907, -122.396954).ToECEF(),
	    0.0,
	    cameraInterestBasis);

	globeCameraController.SetView(cameraInterestBasis, 1781.0);
}

void DynamicText3DExample::Update(float dt)
{
	if(!m_initialised && !m_world.Initialising())
	{
		const Eegeo::v3 salmonPink(255.f/255.f, 145.f/255.f, 164.f/255.f);
		const Eegeo::v3 fullBlue(0.f, 0.f, 1.f);

		CreateDynamic3DText("Transamerica Pyramid", 12, 37.795093,-122.402728, salmonPink, 1.f);
		CreateDynamic3DText("Ferry Building", 18, 37.79561, -122.393351, fullBlue, 0.5f);

		m_initialised = true;
	}
}

void DynamicText3DExample::Suspend()
{
	for(std::vector<PlaceNameView*>::const_iterator it = m_views.begin(); it != m_views.end(); ++it)
	{
		Eegeo_DELETE *it;
	}

	m_views.clear();
	m_initialised = false;
}

void DynamicText3DExample::CreateDynamic3DText(const std::string& str,
        float fontPointSize,
        double latitudeDegrees,
        double longitudeDegrees,
        const Eegeo::v3& colour,
        float alpha)
{
	Eegeo::Space::LatLongAltitude location = Eegeo::Space::LatLongAltitude::FromDegrees(latitudeDegrees, longitudeDegrees, 0.f);
	Eegeo::dv3 posEcef = location.ToECEF();
	Eegeo::Space::CubeMap::CubeMapCellInfo cellInfo(Space::CubeMap::EcefToKey(posEcef, 15));

	std::vector<u32> textUtf32;
	Unicode::UnicodeConverter::Utf8ToUtf32(str.c_str(), textUtf32);

	Resources::PlaceNames::PlaceNameView* pPlaceNameView = m_placeNameViewBuilder.CreatePlaceNameView(textUtf32, "", fontPointSize, posEcef, "", cellInfo);

	if (pPlaceNameView != NULL)
	{
		pPlaceNameView->GetConfig().UpdateColorAndScale(colour, 1.f);
		pPlaceNameView->SetAlpha(alpha);
		m_views.push_back(pPlaceNameView);
	}
}

void DynamicText3DExample::Draw()
{
	bool setMat = false;
	const Rendering::Materials::IMaterial* pMaterial = NULL;
	Rendering::GLState defaultState = m_glState;

	const Camera::RenderCamera& renderCamera = m_cameraProvider.GetRenderCamera();
	const dv3& ecefCameraPosition = renderCamera.GetEcefLocation();
	v3 camSurfaceNormal = ecefCameraPosition.Norm().ToSingle();
	float environmentScale = m_environmentFlatteningService.GetCurrentScale();

	for(std::vector<PlaceNameView*>::const_iterator it = m_views.begin(); it != m_views.end(); ++it)
	{
		PlaceNameView& view = **it;

		view.UpdateTransformsAndVisibility(renderCamera, camSurfaceNormal, 4.0, environmentScale);

		if(view.IsInFrustum() && !view.IsCompletelyTransparent())
		{
			typedef std::vector<PlaceNameRenderable*> TRenderables;
			const TRenderables& renderables = view.GetRenderables();

			for(TRenderables::const_iterator it = renderables.begin(); it != renderables.end(); ++it)
			{
				const Rendering::RenderableBase* pRenderable = *it;;
				pMaterial = pRenderable->GetMaterial();

				if(!setMat)
				{
					pMaterial->SetState(m_glState);
				}

				pRenderable->Render(m_glState);
			}
		}
	}

	if(pMaterial != NULL)
	{
		pMaterial->RestoreState(defaultState, m_glState);
	}
}
}
