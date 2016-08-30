// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "ICallback.h"
#include "Types.h"

#include <memory>

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            class TourRemovedObserver : private Eegeo::NonCopyable
            {
                const std::shared_ptr<ITourRepository> m_tourRepository;
                Eegeo::Helpers::TCallback1<TourRemovedObserver, TourModel> m_binding;
                
                void HandleTourRemoved(TourModel& tourModel);
                
            public:
                TourRemovedObserver(const std::shared_ptr<ITourRepository>& tourRepository);
                
                ~TourRemovedObserver();
            };
        }
    }
}
