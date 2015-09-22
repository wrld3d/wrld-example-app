// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "WorldPins.h"
#include "ICallback.h"
#include "TourWorldPinSelectionHandlerFactory.h"
#include "Types.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            class TourAddedObserver : private Eegeo::NonCopyable
            {
                ITourRepository& m_tourRepository;
                WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                TourWorldPinSelectionHandlerFactory& m_tourWorldPinSelectionHandlerFactory;
                Eegeo::Helpers::TCallback1<TourAddedObserver, TourModel> m_binding;
                
                void HandleTourAdded(TourModel& tourModel);
                
            public:
                TourAddedObserver(ITourRepository& tourRepository,
                                  WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                  TourWorldPinSelectionHandlerFactory& tourWorldPinSelectionHandlerFactory);

                ~TourAddedObserver();
            };
        }
    }
}
