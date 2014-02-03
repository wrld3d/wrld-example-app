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
#include "ShaderCompiler.h"
#include "GlobalLighting.h"
#include "Location.h"
#include "Rendering.h"
#include "SceneElementRepository.h"
#include "IRenderableFilter.h"
#include "GlState.h"
#include "PackedRenderable.h"
#include "GlHelpers.h"

namespace Examples
{
    typedef Eegeo::Rendering::Renderables::PackedRenderable TRenderable;
    typedef TRenderable* TRenderablePtr;
    typedef Eegeo::Rendering::Scene::SceneElement<TRenderable> TSceneElement;
    typedef TSceneElement* TSceneElementPtr;
    typedef std::vector<TSceneElementPtr> TSceneElementPtrVec;
    
    class MyRenderable : public Eegeo::Rendering::RenderableBase
    {
    public:
        MyRenderable(TRenderable& originalRenderable, const Eegeo::Rendering::Materials::IMaterial* pMaterial)
        : Eegeo::Rendering::RenderableBase(Eegeo::Rendering::LayerIds::Buildings, originalRenderable.GetEcefPosition(), pMaterial)
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
    
    typedef Eegeo::Rendering::Scene::ISceneElementObserver<Eegeo::Rendering::Renderables::PackedRenderable> TSceneElementObserver;
    
    class ModifiedRenderingExample : public IExample, TSceneElementObserver, Eegeo::Rendering::IRenderableFilter
    {
    private:
        
        struct MyPoolFilterCriteria : Eegeo::Rendering::Scene::ISceneElementFilterCriteria<TRenderable>
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
        Eegeo::Rendering::Scene::SceneElementRepository<Eegeo::Rendering::Renderables::PackedRenderable>& buildingRepository;
        Eegeo::Rendering::Filters::PackedRenderableFilter& buildingFilter;
        Eegeo::Rendering::RenderQueue& renderQueue;
        Eegeo::Rendering::RenderableFilters& renderableFilters;
        Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator;
        Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator;
        const Eegeo::Helpers::GLHelpers::TextureInfo& placeHolderTexture;
        
        Eegeo::Lighting::GlobalLighting* pAlternativeLighting;
        Eegeo::Rendering::Shaders::PackedDiffuseShader* pAlternativeShader;
        Eegeo::Rendering::Materials::PackedDiffuseMaterial* pAlternativeMaterial;
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
                                 Eegeo::Rendering::Scene::SceneElementRepository<Eegeo::Rendering::Renderables::PackedRenderable>& buildingRepository,
                                 Eegeo::Rendering::Filters::PackedRenderableFilter& buildingFilter,
                                 Eegeo::Rendering::RenderQueue& renderQueue,
                                 Eegeo::Rendering::RenderableFilters& renderableFilters,
                                 Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
                                 Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
                                 const Eegeo::Helpers::GLHelpers::TextureInfo& placeHolderTexture
                                 );
        
        //ISceneElementObserver interface.
        typedef Eegeo::Rendering::Scene::SceneElement<Eegeo::Rendering::Renderables::PackedRenderable> TMySceneElement;
        void OnSceneElementAdded(TMySceneElement& sceneElement);
        void OnSceneElementRemoved(TMySceneElement& sceneElement);
        
        //IRenderableFilter interface.
        void EnqueueRenderables(Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
        
        void Start();
        void Update(float dt);
        void Draw();
        void Suspend();
    };
}

#endif /* defined(__ExampleApp__ModifiedRenderingExample__) */
