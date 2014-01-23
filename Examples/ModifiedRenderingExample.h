//
//  ModifiedRenderingExample.h
//  ExampleApp
//
//  Created by eeGeo on 03/05/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__ModifiedRenderingExample__
#define __ExampleApp__ModifiedRenderingExample__

#include "IExample.h"

#include <vector>
#include "RenderContext.h"
#include "MeshPool.h"
#include "RenderableItem.h"
#include "DiffuseTexturedMaterial.h"
#include "ShaderCompiler.h"
#include "GlobalLighting.h"
#include "Location.h"
#include "Rendering2.h"
#include "SceneElementRepository.h"
#include "IRenderableFilter.h"
#include "GlState.h"
#include "PackedRenderable.h"
#include "GlHelpers.h"

namespace Examples
{
    typedef Eegeo::Rendering2::Renderables::PackedRenderable TRenderable;
    typedef TRenderable* TRenderablePtr;
    typedef Eegeo::Rendering2::Scene::SceneElement<TRenderable> TSceneElement;
    typedef TSceneElement* TSceneElementPtr;
    typedef std::vector<TSceneElementPtr> TSceneElementPtrVec;
    
    class MyRenderable : public Eegeo::Rendering2::RenderableBase
    {
    public:
        MyRenderable(TRenderable& originalRenderable, const Eegeo::Rendering2::Materials::IMaterial* pMaterial)
        : Eegeo::Rendering2::RenderableBase(Eegeo::Rendering2::LayerIds::Buildings, originalRenderable.GetEcefPosition(), pMaterial)
        , m_originalRenderable(originalRenderable)
        {
        }
        
        void Update(Eegeo::Rendering::RenderContext& renderContext)
        {
            m_originalRenderable.CalcUnpackMVP(renderContext, 1.0f);
            m_originalRenderable.SetVisible();
        }
        
        void Render(Eegeo::Rendering::GLState& glState) const
        {
            m_originalRenderable.Render(glState);
        }
        
    private:
        TRenderable& m_originalRenderable;
    };
    
    typedef Eegeo::Rendering2::Scene::ISceneElementObserver<Eegeo::Rendering2::Renderables::PackedRenderable> TSceneElementObserver;
    
    class ModifiedRenderingExample : public IExample, TSceneElementObserver, Eegeo::Rendering2::IRenderableFilter
    {
    private:
        
        struct MyPoolFilterCriteria : Eegeo::Rendering2::Scene::ISceneElementFilterCriteria<TRenderable>
        {
            ModifiedRenderingExample* owner;
        public:
            MyPoolFilterCriteria(ModifiedRenderingExample* owner):owner(owner) {}
            virtual bool FiltersOut(const TSceneElement& item) const;
        };
        
        MyPoolFilterCriteria* pCriteria;
        
        Eegeo::Rendering::RenderContext& renderContext;
        Eegeo::Camera::ICameraProvider& cameraProvider;
        Eegeo::Location::IInterestPointProvider& interestPointProvider;
        Eegeo::Lighting::GlobalLighting& lighting;
        Eegeo::Streaming::IStreamingVolume& visibleVolume;
        Eegeo::Rendering2::Scene::SceneElementRepository<Eegeo::Rendering2::Renderables::PackedRenderable>& buildingRepository;
        Eegeo::Rendering2::Filters::PackedRenderableFilter& buildingFilter;
        Eegeo::Rendering2::RenderQueue& renderQueue;
        Eegeo::Rendering2::RenderableFilters& renderableFilters;
        Eegeo::Rendering2::Shaders::ShaderIdGenerator& shaderIdGenerator;
        Eegeo::Rendering2::Materials::MaterialIdGenerator& materialIdGenerator;
        const Eegeo::Helpers::GLHelpers::TextureInfo& placeHolderTexture;
        
        Eegeo::Lighting::GlobalLighting* pAlternativeLighting;
        Eegeo::Rendering2::Shaders::PackedDiffuseShader* pAlternativeShader;
        Eegeo::Rendering2::Materials::PackedDiffuseMaterial* pAlternativeMaterial;
        typedef std::map<TSceneElementPtr, MyRenderable*> TSceneElementToRenderablePtrMap;
        TSceneElementToRenderablePtrMap alternativeRenderables;
        
        int counter;
        
        bool IsToBeReplacedWithAlternative(const TSceneElement* pSceneElement)  const;
        
    public:
        ModifiedRenderingExample(Eegeo::Rendering::RenderContext& renderContext,
                                 Eegeo::Camera::ICameraProvider& cameraProvider,
                                 Eegeo::Location::IInterestPointProvider& interestPointProvider,
                                 Eegeo::Streaming::IStreamingVolume& visibleVolume,
                                 Eegeo::Lighting::GlobalLighting& lighting,
                                 Eegeo::Rendering2::Scene::SceneElementRepository<Eegeo::Rendering2::Renderables::PackedRenderable>& buildingRepository,
                                 Eegeo::Rendering2::Filters::PackedRenderableFilter& buildingFilter,
                                 Eegeo::Rendering2::RenderQueue& renderQueue,
                                 Eegeo::Rendering2::RenderableFilters& renderableFilters,
                                 Eegeo::Rendering2::Shaders::ShaderIdGenerator& shaderIdGenerator,
                                 Eegeo::Rendering2::Materials::MaterialIdGenerator& materialIdGenerator,
                                 const Eegeo::Helpers::GLHelpers::TextureInfo& placeHolderTexture
                                 );
        
        //ISceneElementObserver interface.
        typedef Eegeo::Rendering2::Scene::SceneElement<Eegeo::Rendering2::Renderables::PackedRenderable> TMySceneElement;
        void OnSceneElementAdded(TMySceneElement& sceneElement);
        void OnSceneElementRemoved(TMySceneElement& sceneElement);
        
        //IRenderableFilter interface.
        void EnqueueRenderables(Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering2::RenderQueue& renderQueue);
        
        void Start();
        void Update(float dt);
        void Draw();
        void Suspend();
    };
}

#endif /* defined(__ExampleApp__ModifiedRenderingExample__) */
