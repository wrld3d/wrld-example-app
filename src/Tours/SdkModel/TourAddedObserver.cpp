// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourAddedObserver.h"
#include "ITourRepository.h"
#include "IWorldPinsService.h"
#include "TourWorldPinSelectionHandler.h"
#include "WorldPinItemModel.h"
#include "WorldPinVisibility.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            TourAddedObserver::TourAddedObserver(ITourRepository& tourRepository,
                                                 WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                 TourWorldPinSelectionHandlerFactory& tourWorldPinSelectionHandlerFactory)
            : m_tourRepository(tourRepository)
            , m_worldPinsService(worldPinsService)
            , m_tourWorldPinSelectionHandlerFactory(tourWorldPinSelectionHandlerFactory)
            , m_binding(this, &TourAddedObserver::HandleTourAdded)
            {
                m_tourRepository.InsertItemAddedCallback(m_binding);
            }
            
            TourAddedObserver::~TourAddedObserver()
            {
                m_tourRepository.RemoveItemAddedCallback(m_binding);
            }
            
            void TourAddedObserver::HandleTourAdded(TourModel& tourModel)
            {
                typedef WorldPins::SdkModel::WorldPinItemModel TPin;
                const int IconIndex = 10;
                
                TPin* pPin = m_worldPinsService.AddPin(m_tourWorldPinSelectionHandlerFactory.CreateSelectionHandler(tourModel),
                                                       NULL,
                                                       WorldPins::SdkModel::WorldPinFocusData(tourModel.Name(), tourModel.IntroText()),
                                                       tourModel.IsInterior(),
                                                       tourModel.WorldPinInteriorData(),
                                                       tourModel.Location(),
                                                       IconIndex,
                                                       0.0f,
                                                       WorldPins::SdkModel::WorldPinVisibility::World);
                
                // map pPin to tourModel somehow, possibly in TourService or another repo.
            }
        }
    }
}
