//
//  ModifiedRenderingExample.cpp
//  ExampleApp
//
//  Created by eeGeo on 03/05/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#include "ModifiedRenderingExample.h"
#include "PooledMesh.h"
#include "IStreamingVolume.h"
#include "DiffuseTexturedVertex.h"
#include "MathsHelpers.h"
#include "IInterestPointProvider.h"
#include "CameraHelpers.h"

using namespace Eegeo;
using namespace Eegeo::Rendering;

namespace Examples
{
    ModifiedRenderingExample::ModifiedRenderingExample(RenderContext& renderContext,
                                                       Eegeo::Camera::ICameraProvider& cameraProvider,
                                                       Eegeo::Location::IInterestPointProvider& interestPointProvider,
                                                       Eegeo::Streaming::IStreamingVolume& visibleVolume,
                                                       Eegeo::Lighting::GlobalLighting& lighting,
                                                       Eegeo::Resources::MeshPool<Eegeo::Rendering::RenderableItem*>& buildingPool,
                                                       Eegeo::Resources::MeshPool<Eegeo::Rendering::RenderableItem*>& shadowPool)
    :renderContext(renderContext)
    ,cameraProvider(cameraProvider)
    ,interestPointProvider(interestPointProvider)
    ,visibleVolume(visibleVolume)
    ,buildingPool(buildingPool)
    ,shadowPool(shadowPool)
    ,lighting(lighting)
    ,pCriteria(NULL)
    {
    }
    
    void ModifiedRenderingExample::Start()
    {
        //MyPoolFilterCriteria implemented below... uses camera interest point as selection criteria
        pCriteria = new ModifiedRenderingExample::MyPoolFilterCriteria(this);
        
        //apply to pools, but lifetime responsibility is ours
        buildingPool.SetFilterCriteria(pCriteria);
        shadowPool.SetFilterCriteria(pCriteria);
    }
    
    void ModifiedRenderingExample::Suspend()
    {
        //remove it from the pools, and destroy the criteria
        buildingPool.SetFilterCriteria(NULL);
        shadowPool.SetFilterCriteria(NULL);
        
        delete pCriteria;
        pCriteria = NULL;
    }
    
    void ModifiedRenderingExample::Update()
    {
        
    }
    
    void ModifiedRenderingExample::Draw()
    {
        //i want to draw the buildings matching the criteria a flat color and transparent...
        //if shadows match the filter criteria, just don't draw them
        //
        //if the buildings match, DrawItems uses my shader and sets state to draw transparently
        
        typedef Eegeo::Resources::PooledMesh<RenderableItem*>* TPooledMeshPtr;
        typedef Eegeo::DataStructures::PoolEntry<TPooledMeshPtr> TPoolEntry;
        typedef std::vector<TPoolEntry> TResVec;
        
        TResVec filtered;
        buildingPool.GetEntriesMeetingFilterCriteria(filtered);
        
        std::vector<RenderableItem*> toRender;
        
        for(TResVec::const_iterator it = filtered.begin(); it != filtered.end(); ++ it)
        {
            const TPoolEntry& item = *it;
            RenderableItem* resource = item.instance->GetResource();
            
            if(item.allocated && resource != NULL && item.instance->ShouldDraw())
            {
                toRender.push_back(resource);
            }
        }
        
        //ok, the toRender items were not drawn by the platform, so I should draw them now
        DrawItems(toRender);
    }
    
    void ModifiedRenderingExample::DrawItems(const std::vector<Eegeo::Rendering::RenderableItem*>& items)
    {
        GLState& glState = renderContext.GetGLState();
        
        std::vector<Eegeo::Culling::IndexBufferRange> rangesToDraw;
        
        if (glState.UseProgram.TrySet(shader.ProgramHandle))
        {
            const Eegeo::m44 &colors = lighting.GetColors();
            Eegeo_GL(glUniformMatrix4fv(shader.LightColorsUniform, 1, 0, (const GLfloat*)&colors));
        }
        
        for(std::vector<RenderableItem*>::const_iterator it = items.begin(); it != items.end(); ++ it)
        {
            RenderableItem* item = *it;
            
            if(item->IndexCount() == 0) {
                continue;
            }
            
            //semt-transparent, so we're gonna be blending
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            
            Eegeo::v3 cameraLocalPos = Eegeo::Camera::CameraHelpers::CameraRelativePoint(item->GetEcefPosition(), renderContext.GetCameraOriginEcef());

            Eegeo::m44 model, mvp;
            Helpers::MathsHelpers::ComputeScaleAndOffset(model, 1.0f, item->GetEcefPosition().Norm().ToSingle(), cameraLocalPos);
            Eegeo::m44::Mul(mvp, renderContext.GetViewProjectionMatrix(), model);
            
            Eegeo_GL(glUniformMatrix4fv(shader.ModelViewProjectionUniform, 1, 0, (const GLfloat*)&mvp))
            
            Eegeo_GL(glUniform3f(shader.MinVertRangeUniform,
                                 item->GetMinVertexRange().GetX(),
                                 item->GetMinVertexRange().GetY(),
                                 item->GetMinVertexRange().GetZ()));
            
            Eegeo_GL(glUniform3f(shader.MaxVertRangeUniform,
                                 item->GetMaxVertexRange().GetX(),
                                 item->GetMaxVertexRange().GetY(),
                                 item->GetMaxVertexRange().GetZ()));
            
            Eegeo_GL(glUniform4f(shader.DiffuseColorUniform, 0.0f, 0.0f, 1.0f, 0.1f)); //alpha 10%
            
            Eegeo_GL(glEnableVertexAttribArray(shader.PositionAttribute));
            Eegeo_GL(glEnableVertexAttribArray(shader.LightDotAttribute));
            
            glState.BindArrayBuffer(item->GetVertexBuffer());
            glState.BindElementArrayBuffer(item->GetIndexBuffer());
            
            //i don't need the UV channel as not texturing them, but it is part of the buulding vertex so must be considered
            Eegeo_GL(glVertexAttribPointer(shader.PositionAttribute, 3, GL_UNSIGNED_SHORT, GL_TRUE, sizeof(ShortDiffuseTexturedVertex), 0));
            Eegeo_GL(glVertexAttribPointer(shader.LightDotAttribute, 1, GL_FLOAT, GL_FALSE, sizeof(ShortDiffuseTexturedVertex), (GLvoid*) (sizeof(short)*6)));
            
            Eegeo_GL(glDrawElements(GL_TRIANGLES, item->IndexCount(), GL_UNSIGNED_SHORT, (void*)0 ));
            
        }
        
        glDisable(GL_BLEND);
        glState.BindArrayBuffer(0);
        glState.BindElementArrayBuffer(0);
    }
    
    bool ModifiedRenderingExample::MyPoolFilterCriteria::operator()(Eegeo::Rendering::RenderableItem* item)
    {
        const double filterRadius = 400.0f;
        const double filterRadiusSq = filterRadius*filterRadius;
        
        Eegeo::v3 cameraRelativePos = Eegeo::Camera::CameraHelpers::CameraRelativePoint(item->GetEcefPosition(), owner->interestPointProvider.GetEcefInterestPoint());
        
        double delta = cameraRelativePos.LengthSq();
        bool closeToInterest = delta < filterRadiusSq;
        
        if (closeToInterest)
        {
            return true; //i want to draw with custom semi-transparent rendering method
        }
        
        return false; //let the platform do the default rendering 
    }
}