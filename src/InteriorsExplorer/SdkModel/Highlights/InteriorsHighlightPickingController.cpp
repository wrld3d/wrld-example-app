// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorsHighlightPickingController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                InteriorsHighlightPickingController::InteriorsHighlightPickingController(Eegeo::Collision::IRayCaster& rayCaster,
                                                                                         const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                                         Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService)
                : PickingController(rayCaster, interiorInteractionModel, environmentFlatteningService, Eegeo::Collision::CollisionGroup::Highlights)
                {
                    
                }
                
                void InteriorsHighlightPickingController::ProcessRayCastResult(const Eegeo::Collision::RayCasterResult& pickResult)
                {
                    //            if(pickResult.intersects)
                    //            {
                    //                const std::string materialId = pickResult.pCollisionBvh->CollisionMaterialIdForIndex(pickResult.collisionMaterialIndex);
                    //
                    //                const Resources::Interiors::InteriorsModel *model = NULL;
                    //
                    //                if(m_interiorsController.TryGetCurrentModel(model))
                    //                {
                    //                    for (int floorIndex = 0; floorIndex < model->GetFloorCount(); ++floorIndex)
                    //                    {
                    //                        int floorNumber = model->GetFloorAtIndex(floorIndex).GetFloorNumber();
                    //                        Eegeo::Resources::Interiors::InteriorsFloorCells* floorCells = model->GetFloorCells(floorNumber);
                    //
                    //                        for (int cellIndex = 0; cellIndex < floorCells->GetCellCount(); ++cellIndex)
                    //                        {
                    //                            Eegeo::Resources::Interiors::InteriorsFloorCell* cell = floorCells->GetFloorCells()[cellIndex];
                    //
                    //                            std::vector<Rendering::Renderables::InteriorHighlightRenderable*> renderables = cell->GetHighlightRenderables();
                    //
                    //                            for (std::vector<Rendering::Renderables::InteriorHighlightRenderable*>::iterator renderable = renderables.begin();
                    //                                 renderable != renderables.end();
                    //                                 ++renderable)
                    //                            {
                    //                                Rendering::Renderables::InteriorHighlightRenderable* pCurrentRenderable = (*renderable);
                    //                                const std::string& renderableId = pCurrentRenderable->GetRenderableId();
                    //
                    //                                pCurrentRenderable->GetInteriorTerrainHeight();
                    //
                    //                                if (renderableId == materialId)
                    //                                {
                    //                                    if(pCurrentRenderable->GetDiffuseColor().GetX() == 1.0f && pCurrentRenderable->GetDiffuseColor().GetY() == 1.0f)
                    //                                        pCurrentRenderable->SetDiffuseColor(v4(0.0f, 1.0f, 0.0f, 0.3f));
                    //                                    else if(pCurrentRenderable->GetDiffuseColor().GetY() == 1.0f)
                    //                                        pCurrentRenderable->SetDiffuseColor(v4(1.0f, 0.0f, 0.0f, 0.3f));
                    //                                    else
                    //                                        pCurrentRenderable->SetDiffuseColor(v4(1.0f, 1.0f, 0.0f, 0.3f));
                    //
                    //                                    return;
                    //                                }
                    //                            }
                    //                        }
                    //                    }
                    //              }
                    //            }
                }
            }
        }
    }
}