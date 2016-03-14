// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DesktopSearchResultPoiController.h"
#include "SearchResultPoiViewOpenedMessage.h"
#include "SearchResultPoiViewClosedMessage.h"
#include "SearchJsonParser.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {   
            DesktopSearchResultPoiController::DesktopSearchResultPoiController(ISearchResultPoiView& view,
                                                                               ISearchResultPoiViewModel& viewModel,
                                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                                               Metrics::IMetricsService& metricsService):
                SearchResultPoiController(view,
                                          viewModel,
                                          messageBus,
                                          metricsService)
            {
            }

            DesktopSearchResultPoiController::~DesktopSearchResultPoiController()
            {
            }

            void DesktopSearchResultPoiController::OnViewOpened()
            {
                const Search::SdkModel::SearchResultModel& searchResultModel = GetViewModel().GetSearchResultModel();

                GetView().Show(searchResultModel, GetViewModel().IsPinned());

                std::string imageUrl = "";
                Search::SdkModel::TryParseImageDetails(searchResultModel, imageUrl);
                GetMessageBus().Publish(SearchResultPoiViewOpenedMessage(imageUrl));
            }
        }
    }
}
