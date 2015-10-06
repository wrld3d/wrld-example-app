// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ExampleTourPinSelectionHandler.h"
#include "TourModel.h"
#include "SearchResultModel.h"
#include "SearchResultOnMapItemModelSelectedMessage.h"
#include "TimeHelpers.h"
#include <string>
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include "SearchVendorNames.h"

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
                        Search::SdkModel::SearchResultModel model(Search::SdkModel::SearchResultModel::CurrentVersion,
                                                                  "",
                                                                  m_stateModel.Headline(),
                                                                  m_stateModel.Description(),
                                                                  Eegeo::Space::LatLong::FromDegrees(0.0f,
                                                                                                     0.0f),
                                                                  0,
                                                                  false,
                                                                  Eegeo::Resources::Interiors::InteriorId(""),
                                                                  0,
                                                                  "",
                                                                  std::vector<std::string>(),
                                                                  Search::ExampleTourVendorName,
                                                                  CreateJsonData(),
                                                                  Eegeo::Helpers::Time::MillisecondsSinceEpoch());
                        
                        m_messageBus.Publish(SearchResultOnMap::SearchResultOnMapItemModelSelectedMessage(model));
                        
                    }
                    
                    std::string ExampleTourPinSelectionHandler::CreateJsonData()
                    {
                        rapidjson::Document jsonDoc;
                        rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                        rapidjson::Value valueObject(rapidjson::kObjectType);
                        
                        valueObject.AddMember("imageUrl", m_stateModel.ImagePath().c_str(), allocator);
                        
                        rapidjson::StringBuffer strbuf;
                        rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                        valueObject.Accept(writer);
                        return strbuf.GetString();
                    }
                }
            }
        }
    }
}
