//
//  ModifiedRenderingExample.cpp
//  ExampleApp
//
//  Created by eeGeo on 03/05/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

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
                                                       const Eegeo::Helpers::GLHelpers::TextureInfo& placeHolderTexture
                                                       )
    :renderContext(renderContext)
    ,cameraProvider(cameraProvider)
    ,interestPointProvider(interestPointProvider)
    ,visibleVolume(visibleVolume)
    ,buildingRepository(buildingRepository)
    ,buildingFilter(buildingFilter)
    ,lighting(lighting)
    ,pCriteria(NULL)
    ,renderQueue(renderQueue)
    ,renderableFilters(renderableFilters)
    ,shaderIdGenerator(shaderIdGenerator)
    ,materialIdGenerator(materialIdGenerator)
    ,placeHolderTexture(placeHolderTexture)
    {
    }
    
    void ModifiedRenderingExample::Start()
    {
        //MyPoolFilterCriteria implemented below... uses camera interest point as selection criteria
        pCriteria = new ModifiedRenderingExample::MyPoolFilterCriteria(this);
        
        //apply to filter, but lifetime responsibility is ours
        buildingFilter.SetFilterCriteria(pCriteria);
        
        //register for notifications when scene elements are added to or removed from the scene.
        buildingRepository.AddObserver(*this);
        
        //register as a renderable filter so that we can submit our new renderables for rendering.
        renderableFilters.AddRenderableFilter(this);
        
        // create alternative material to render with.
        pAlternativeLighting = Eegeo_NEW(Eegeo::Lighting::GlobalLighting)();
        
        pAlternativeShader = Eegeo::Rendering::Shaders::PackedDiffuseShader::Create(shaderIdGenerator.GetNextId());
        
        pAlternativeMaterial = Eegeo_NEW(Eegeo::Rendering::Materials::PackedDiffuseMaterial)(
                                                                                              materialIdGenerator.GetNextId(),
                                                                                              "ExampleMaterial",
                                                                                              *pAlternativeShader,
                                                                                              *pAlternativeLighting,
                                                                                              placeHolderTexture.textureId,
                                                                                              Eegeo::Rendering::TextureMinify_NearestMipmap_Linear,
                                                                                              false,
                                                                                              false);
    }
    
    void ModifiedRenderingExample::Suspend()
    {
        Eegeo_DELETE(pAlternativeMaterial);
        Eegeo_DELETE(pAlternativeShader);
        Eegeo_DELETE(pAlternativeLighting);
        
        // unregister for rendering.
        renderableFilters.RemoveRenderableFilter(this);
        
        // un-register from receiving scene element notifications.
        buildingRepository.RemoveObserver(*this);
        
        //remove it from the pools, and destroy the criteria
        buildingFilter.SetFilterCriteria(NULL);
        
        delete pCriteria;
        pCriteria = NULL;
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
            MyRenderable* pAlternativeRenderable = Eegeo_NEW(MyRenderable)(*pOriginalRenderable, pAlternativeMaterial);

            //add the alternative to our list of renderables.
            alternativeRenderables.insert(std::pair<TSceneElementPtr, MyRenderable*>(&sceneElement, pAlternativeRenderable));
        }
    }
    
    void ModifiedRenderingExample::OnSceneElementRemoved(TMySceneElement& sceneElement)
    {
        TSceneElementToRenderablePtrMap::iterator it = alternativeRenderables.find(&sceneElement);
        
        if(it != alternativeRenderables.end())
        {
            Eegeo_DELETE(it->second);
            alternativeRenderables.erase(it);
        }
    }

    bool ModifiedRenderingExample::IsToBeReplacedWithAlternative(const TSceneElement* pSceneElement)  const
    {
        const TRenderable& renderable = pSceneElement->GetResource();
        
        if(!renderable.GetMaterial()->GetName().compare(Eegeo::Rendering::MaterialNames::Buildings))
        {
            const double filterRadius = 400.0f;
            const double filterRadiusSq = filterRadius*filterRadius;
            
            Eegeo::v3 cameraRelativePos = Eegeo::Camera::CameraHelpers::CameraRelativePoint(renderable.GetEcefPosition(), interestPointProvider.GetEcefInterestPoint());
            
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
        for(TSceneElementToRenderablePtrMap::const_iterator it = alternativeRenderables.begin(); it != alternativeRenderables.end(); ++it)
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
        return owner->IsToBeReplacedWithAlternative(&sceneElement);
    }
}