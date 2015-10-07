// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ExampleTourHelpers.h"
#include <vector>
#include "SearchResultModel.h"
#include "TimeHelpers.h"
#include "SearchVendorNames.h"
#include "TourStateModel.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

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
                    Search::SdkModel::SearchResultModel CreateSearchResultModelFromTourStateModel(const TourStateModel& model)
                    {
                        
                        Search::SdkModel::SearchResultModel searchResultModel(Search::SdkModel::SearchResultModel::CurrentVersion,
                                                                  "",
                                                                  model.Headline(),
                                                                  model.Description(),
                                                                  Eegeo::Space::LatLong::FromDegrees(0.0f,
                                                                                                     0.0f),
                                                                  0,
                                                                  false,
                                                                  Eegeo::Resources::Interiors::InteriorId(""),
                                                                  0,
                                                                  model.Icon(),
                                                                  std::vector<std::string>(),
                                                                  Search::ExampleTourVendorName,
                                                                  CreateJsonDataFromTourStateModel(model),
                                                                  Eegeo::Helpers::Time::MillisecondsSinceEpoch());
                        
                        return searchResultModel;
                    }
                    
                    std::string CreateJsonDataFromTourStateModel(const TourStateModel& model)
                    {
                        rapidjson::Document jsonDoc;
                        rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                        rapidjson::Value valueObject(rapidjson::kObjectType);
                        
                        valueObject.AddMember("imageUrl", model.ImagePath().c_str(), allocator);
                        
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