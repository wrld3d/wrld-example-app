// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinSelectionHandler.h"
#include "Tours.h"
#include <string>

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace TwitterFeed
                {
                    class TwitterFeedPinSelectionHandler : public WorldPins::SdkModel::IWorldPinSelectionHandler
                    {
                    private:
                        std::string m_tourName;
                        ITourRepository& m_tourRepository;
                        ITourService& m_tourService;
                        
                    public:
                        TwitterFeedPinSelectionHandler(const std::string& tourName,
                                                       ITourRepository& tourRepository,
                                                       ITourService& tourService);
                        ~TwitterFeedPinSelectionHandler();
                        
                        void SelectPin();
                    };
                }
            }
        }
    }
}
