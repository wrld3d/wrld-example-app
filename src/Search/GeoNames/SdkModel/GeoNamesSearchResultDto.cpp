// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include <vector>
#include "GeoNamesSearchResultDto.h"
#include "SearchResultModel.h"
#include "SearchVendorNames.h"
#include "TimeHelpers.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                GeoNamesSearchResultDto::GeoNamesSearchResultDto(const std::string& id,
                                                                 const std::string& name,
                                                                 const std::string& country,
                                                                 const Eegeo::Space::LatLong& location,
                                                                 int population)
                : m_id(id)
                , m_name(name)
                , m_country(country)
                , m_location(location)
                {
                    
                }
                
                Search::SdkModel::SearchResultModel GeoNamesSearchResultDto::ToSearchResultModel() const
                {
                    // TODO tags: would be nice to have a mechanism to resolve unknown tags for icons
                    // downstream for non-eegeo types?
                    // also: would be cool to do something to use a more specific icon for countries/regions/lakes/hamlets etc.
                    std::vector<std::string> tags = { "pin" };
                    Search::SdkModel::TagIconKey tagIconKey = "pin";

                    Search::SdkModel::SearchResultModel model(Search::SdkModel::SearchResultModel::CurrentVersion,
                                                              m_id,
                                                              m_name,
                                                              m_country,
                                                              Eegeo::Space::LatLong::FromDegrees(m_location.GetLatitudeInDegrees(),
                                                                                                 m_location.GetLongitudeInDegrees()),
                                                              0,
                                                              false,
                                                              Eegeo::Resources::Interiors::InteriorId(""),
                                                              0,                                                              
                                                              tags,
                                                              std::vector<std::string>(),
                                                              tagIconKey,
                                                              Search::GeoNamesVendorName,
                                                              "",
                                                              Eegeo::Helpers::Time::MillisecondsSinceEpoch());
                    
                    return model;
                }
            }
        }
    }
}
