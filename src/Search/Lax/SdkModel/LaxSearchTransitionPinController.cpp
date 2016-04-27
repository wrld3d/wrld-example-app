// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "LaxSearchTransitionPinController.h"

#include "IWorldPinsService.h"
#include "LaxSearchParser.h"
#include "LaxSearchTransitionPinSelectionHandler.h"
#include "WorldPinVisibility.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                LaxSearchTransitionPinController::LaxSearchTransitionPinController(WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                                                           CameraTransitions::SdkModel::ICameraTransitionController& transitionController,
                                                                                           AppCamera::SdkModel::IAppCameraController& appCameraController)
                : m_worldPinsService(worldPinsService)
                , m_transitionController(transitionController)
                , m_appCameraController(appCameraController)
                , Eegeo::Helpers::TCallback1<LaxSearchTransitionPinController, const std::vector<Search::SdkModel::SearchResultModel>&>(this, &LaxSearchTransitionPinController::OnTransitionsLoaded)
                {
                    
                }
                
                LaxSearchTransitionPinController::~LaxSearchTransitionPinController()
                {
                    ClearResults();
                }
                
                void LaxSearchTransitionPinController::OnTransitionsLoaded(const std::vector<Search::SdkModel::SearchResultModel>& transitionResults)
                {
                    ClearResults();
                    
                    for(std::vector<Search::SdkModel::SearchResultModel>::const_iterator it = transitionResults.begin(); it != transitionResults.end(); ++it)
                    {
                        WorldPins::SdkModel::WorldPinFocusData worldPinFocusData("Exit", "", it->GetVendor());
                        WorldPins::SdkModel::WorldPinInteriorData worldPinInteriorData((*it).GetBuildingId(),
                                                                                       (*it).GetFloor());
                        
                        const float heightOffsetMetres = 0.0f;
                        const int iconIndex = m_searchResultIconCategoryMapper.GetIconIndexFromSearchResult(*it);
                        const bool isInteriorPin = true;
                        
                        LaxTransitionResultModel transitionResultModel = SearchParser::TransformToLaxTransitionResult(*it);
                        
                        WorldPins::SdkModel::WorldPinItemModel* pPinItemModel = m_worldPinsService.AddPin(Eegeo_NEW(LaxSearchTransitionPinSelectionHandler)(
                                                                                                                                                                transitionResultModel,
                                                                                                                                                                m_transitionController,
                                                                                                                                                                m_appCameraController),
                                                                                                          NULL,
                                                                                                          worldPinFocusData,
                                                                                                          isInteriorPin,
                                                                                                          worldPinInteriorData,
                                                                                                          (*it).GetLocation(),
                                                                                                          iconIndex,
                                                                                                          heightOffsetMetres,
                                                                                                          WorldPins::SdkModel::WorldPinVisibility::All);
                        pPinItemModel->SetFocusable(false);
                        
                        m_transitionPins.push_back(pPinItemModel);
                    }
                }
                
                void LaxSearchTransitionPinController::ClearResults()
                {
                    for(std::vector<WorldPins::SdkModel::WorldPinItemModel*>::const_iterator it = m_transitionPins.begin(); it != m_transitionPins.end(); ++it)
                    {
                        m_worldPinsService.RemovePin(*it);
                    }
                    
                    m_transitionPins.clear();
                }
            }
        }
    }
}