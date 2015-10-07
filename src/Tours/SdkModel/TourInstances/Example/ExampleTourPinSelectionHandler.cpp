// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ExampleTourPinSelectionHandler.h"
#include "TourModel.h"
#include "SearchResultModel.h"
#include "SearchResultOnMapItemModelSelectedMessage.h"
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
                    ExampleTourPinSelectionHandler::ExampleTourPinSelectionHandler(ExampleAppMessaging::TMessageBus& messageBus,TourStateModel& stateModel)
                    : m_messageBus(messageBus)
                    , m_stateModel(stateModel)
                    { }
                    
                    void ExampleTourPinSelectionHandler::SelectPin()
                    {
                        Search::SdkModel::SearchResultModel model = CreateSearchResultModelFromTourStateModel(m_stateModel);
                        
                        m_messageBus.Publish(SearchResultOnMap::SearchResultOnMapItemModelSelectedMessage(model));
                        
                    }
                }
            }
        }
    }
}
