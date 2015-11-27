// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TwitterFeedPinSelectionHandler.h"
#include "TourModel.h"
#include "ITourService.h"
#include "ITourRepository.h"

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
                    TwitterFeedPinSelectionHandler::TwitterFeedPinSelectionHandler(const std::string& tourName,
                                                                                   ITourRepository& tourRepository,
                                                                                   ITourService& tourService)
                    : m_tourName(tourName)
                    , m_tourRepository(tourRepository)
                    , m_tourService(tourService)
                    {
                        
                    }
                    
                    TwitterFeedPinSelectionHandler::~TwitterFeedPinSelectionHandler()
                    {
                        
                    }
                    
                    void TwitterFeedPinSelectionHandler::SelectPin()
                    {
                        Eegeo_TTY(m_tourName.c_str());
                        if(m_tourRepository.ContainsTourModelWithName(m_tourName))
                        {
                            TourModel tourModel = m_tourRepository.GetTourModelWithName(m_tourName);
                            
                            m_tourService.EnqueueNextTour(tourModel);
                        }
                    }
                }
            }
        }
    }
}
