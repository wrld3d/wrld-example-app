// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ExampleCurrentTourCardTappedHandler.h"
#include "TourModel.h"
#include "SearchResultModel.h"
#include "SearchResultOnMapItemModelSelectedMessage.h"
#include "TimeHelpers.h"
#include <string>
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include "SearchVendorNames.h"
#include "ExampleTourHelpers.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace Example
                {
                    ExampleCurrentTourCardTappedHandler::ExampleCurrentTourCardTappedHandler(ExampleAppMessaging::TMessageBus& messageBus,TourStateModel& stateModel)
                    : m_messageBus(messageBus)
                    , m_stateModel(stateModel)
                    , m_currentTourCardTappedCallback(this, &ExampleCurrentTourCardTappedHandler::OnCurrentTourCardTapped)
                    {
                        m_messageBus.SubscribeNative(m_currentTourCardTappedCallback);
                    }
                    
                    ExampleCurrentTourCardTappedHandler::~ExampleCurrentTourCardTappedHandler()
                    {
                        m_messageBus.UnsubscribeNative(m_currentTourCardTappedCallback);
                    }
                    
                    void ExampleCurrentTourCardTappedHandler::OnCurrentTourCardTapped(const CurrentTourCardTappedMessage& message)
                    {
                        Search::SdkModel::SearchResultModel model = CreateSearchResultModelFromTourStateModel(m_stateModel);
                        
                        m_messageBus.Publish(SearchResultOnMap::SearchResultOnMapItemModelSelectedMessage(model));
                        
                    }
                }
            }
        }
    }
}
