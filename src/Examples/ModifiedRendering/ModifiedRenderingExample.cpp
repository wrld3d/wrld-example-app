// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ModifiedRenderingExample.h"
#include "IStreamingVolume.h"
#include "MathsHelpers.h"
#include "IInterestPointProvider.h"
#include "CameraHelpers.h"
#include "PackedRenderable.h"
#include "RenderQueue.h"
#include "PackedRenderableFilter.h"
#include "RenderableFilters.h"
#include "PackedDiffuseShader.h"
#include "PackedDiffuseMaterial.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "CityThemeState.h"
#include "EnvironmentTextures.h"
#include "MortonKey.h"
#include "MaterialNames.h"

using namespace Eegeo;
using namespace Eegeo::Rendering;

namespace Examples
{
ModifiedRenderingExample::ModifiedRenderingExample(RenderContext& renderContext,
        Eegeo::Camera::ICameraProvider& cameraProvider,
        Eegeo::Location::IInterestPointProvider& interestPointProvider,
        Eegeo::Streaming::IStreamingVolume& visibleVolume,
        Eegeo::Lighting::GlobalLighting& lighting,
        Eegeo::Rendering::Scene::SceneElementRepository<Eegeo::Rendering::Renderables::PackedRenderable>& buildingRepository,
        Eegeo::Rendering::Filters::PackedRenderableFilter& buildingFilter,
        Eegeo::Rendering::RenderQueue& renderQueue,
        Eegeo::Rendering::RenderableFilters& renderableFilters,
        Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
        Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
        const Eegeo::Helpers::GLHelpers::TextureInfo& placeHolderTexture,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController
                                                  )
	:m_renderContext(renderContext)
	,m_cameraProvider(cameraProvider)
	,m_interestPointProvider(interestPointProvider)
	,m_visibleVolume(visibleVolume)
	,m_buildingRepository(buildingRepository)
	,m_buildingFilter(buildingFilter)
	,m_lighting(lighting)
	,m_pCriteria(NULL)
	,m_renderQueue(renderQueue)
	,m_renderableFilters(renderableFilters)
	,m_shaderIdGenerator(shaderIdGenerator)
	,m_materialIdGenerator(materialIdGenerator)
	,m_placeHolderTexture(placeHolderTexture)
	,m_globeCameraStateRestorer(cameraController)
{
}

void ModifiedRenderingExample::Start()
{
	//MyPoolFilterCriteria implemented below... uses camera interest point as selection criteria
	m_pCriteria = new ModifiedRenderingExample::MyPoolFilterCriteria(this);

	//apply to filter, but lifetime responsibility is ours
	m_buildingFilter.SetFilterCriteria(m_pCriteria);

	//register for notifications when scene elements are added to or removed from the scene.
	m_buildingRepository.AddObserver(*this);

	//register as a renderable filter so that we can submit our new renderables for rendering.
	m_renderableFilters.AddRenderableFilter(this);

	// create alternative material to render with.
	m_pAlternativeLighting = Eegeo_NEW(Eegeo::Lighting::GlobalLighting)();

	m_pAlternativeShader = Eegeo::Rendering::Shaders::PackedDiffuseShader::Create(m_shaderIdGenerator.GetNextId());

	m_pAlternativeMaterial = Eegeo_NEW(Eegeo::Rendering::Materials::PackedDiffuseMaterial)(
	                             m_materialIdGenerator.GetNextId(),
	                             "ExampleMaterial",
	                             *m_pAlternativeShader,
	                             *m_pAlternativeLighting,
	                             m_placeHolderTexture.textureId,
	                             Eegeo::Rendering::TextureMinify_NearestMipmap_Linear,
	                             false,
	                             false);
}

void ModifiedRenderingExample::Suspend()
{
	Eegeo_DELETE(m_pAlternativeMaterial);
	Eegeo_DELETE(m_pAlternativeShader);
	Eegeo_DELETE(m_pAlternativeLighting);

	// unregister for rendering.
	m_renderableFilters.RemoveRenderableFilter(this);

	// un-register from receiving scene element notifications.
	m_buildingRepository.RemoveObserver(*this);

	//remove it from the pools, and destroy the criteria
	m_buildingFilter.SetFilterCriteria(NULL);

	delete m_pCriteria;
	m_pCriteria = NULL;
}

void ModifiedRenderingExample::Update(float dt)
{
}

void ModifiedRenderingExample::Draw()
{
}

void ModifiedRenderingExample::OnSceneElementAdded(TMySceneElement& sceneElement)
{
	const TRenderablePtr pOriginalRenderable = &(sceneElement.GetResource());

	if(!pOriginalRenderable->GetMaterial()->GetName().compare(Eegeo::Rendering::MaterialNames::Buildings))
	{
		//create an alternative renderable with a our own alternative material.
		MyRenderable* pAlternativeRenderable = Eegeo_NEW(MyRenderable)(*pOriginalRenderable, m_pAlternativeMaterial);

		//add the alternative to our list of renderables.
		m_alternativeRenderables.insert(std::pair<TSceneElementPtr, MyRenderable*>(&sceneElement, pAlternativeRenderable));
	}
}

void ModifiedRenderingExample::OnSceneElementRemoved(TMySceneElement& sceneElement)
{
	TSceneElementToRenderablePtrMap::iterator it = m_alternativeRenderables.find(&sceneElement);

	if(it != m_alternativeRenderables.end())
	{
		Eegeo_DELETE(it->second);
		m_alternativeRenderables.erase(it);
	}
}

bool ModifiedRenderingExample::IsToBeReplacedWithAlternative(const TSceneElement* pSceneElement)  const
{
	const TRenderable& renderable = pSceneElement->GetResource();

	if(!renderable.GetMaterial()->GetName().compare(Eegeo::Rendering::MaterialNames::Buildings))
	{
		const double filterRadius = 400.0f;
		const double filterRadiusSq = filterRadius*filterRadius;

		Eegeo::v3 cameraRelativePos = Eegeo::Camera::CameraHelpers::CameraRelativePoint(renderable.GetEcefPosition(), m_interestPointProvider.GetEcefInterestPoint());

		double delta = cameraRelativePos.LengthSq();
		bool closeToInterest = delta < filterRadiusSq;

		if (closeToInterest)
		{
			return true;
		}
	}

	return false;
}

void ModifiedRenderingExample::EnqueueRenderables(Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
{
	for(TSceneElementToRenderablePtrMap::const_iterator it = m_alternativeRenderables.begin(); it != m_alternativeRenderables.end(); ++it)
	{
		if(it->first->IsInSceneGraph() && IsToBeReplacedWithAlternative(it->first))
		{
			MyRenderable* pRenderable = it->second;

			pRenderable->Update(renderContext);
			renderQueue.EnqueueRenderable(pRenderable);
		}
	}
}

bool ModifiedRenderingExample::MyPoolFilterCriteria::FiltersOut(const TSceneElement& sceneElement) const
{
	return m_pOwner->IsToBeReplacedWithAlternative(&sceneElement);
}
}