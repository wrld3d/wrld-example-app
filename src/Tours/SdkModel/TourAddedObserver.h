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
                const std::shared_ptr<ITourRepository> m_tourRepository;
                const std::shared_ptr<WorldPins::SdkModel::IWorldPinsService> m_worldPinsService;
                const std::shared_ptr<TourWorldPinSelectionHandlerFactory> m_tourWorldPinSelectionHandlerFactory;
                Eegeo::Helpers::TCallback1<TourAddedObserver, TourModel> m_binding;
                
                void HandleTourAdded(TourModel& tourModel);
                
            public:
                TourAddedObserver(const std::shared_ptr<ITourRepository>& tourRepository,
                                  const std::shared_ptr<WorldPins::SdkModel::IWorldPinsService>& worldPinsService,
                                  const std::shared_ptr<TourWorldPinSelectionHandlerFactory>& tourWorldPinSelectionHandlerFactory);

                ~TourAddedObserver();
            };
        }
    }
}
