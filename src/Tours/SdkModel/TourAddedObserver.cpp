// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourModel.h"
#include "TourAddedObserver.h"
#include "ITourRepository.h"
#include "IWorldPinsService.h"
#include "TourWorldPinSelectionHandler.h"
#include "WorldPinItemModel.h"
#include "WorldPinVisibility.h"
#include "SearchVendorNames.h"
#include "ColorHelpers.h"

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
                if (tourModel.IsVisibleOnMap())
                {
                    typedef WorldPins::SdkModel::WorldPinItemModel TPin;

                    const std::string tourVendor = tourModel.UsesTwitter()? Search::WorldTwitterVendorName : Search::ExampleTourVendorName;
                    TPin* pPin = m_worldPinsService.AddPin(m_tourWorldPinSelectionHandlerFactory.CreateSelectionHandler(tourModel),
                                                           NULL,
                                                           WorldPins::SdkModel::WorldPinFocusData(tourModel.Name(),
                                                                                                  tourModel.IntroText(),
                                                                                                  tourVendor,
                                                                                                  GenerateTourHovercardJsonData(tourModel),
                                                                                                  "",
                                                                                                  0),
                                                           tourModel.IsInterior(),
                                                           tourModel.WorldPinInteriorData(),
                                                           tourModel.Location(),
                                                           tourModel.PinIconKey(),
                                                           0.0f,
                                                           WorldPins::SdkModel::WorldPinVisibility::World);
                    
                    pPin->SetFocusable(true); // Added to stop unused variable warning. May also prove useful in future to set focusable from tourModel
                    
                    // map pPin to tourModel somehow, possibly in TourService or another repo.
                }
            }
        }
    }
}
