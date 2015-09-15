// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include <vector>
#include "GeoNamesSearchResultDto.h"
#include "SearchResultModel.h"
#include "TimeHelpers.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            GeoNamesSearchResultDto::GeoNamesSearchResultDto(const std::string& name,
                                                             const std::string& country,
                                                             const Eegeo::Space::LatLong& location,
                                                             int population)
            : m_name(name)
            , m_country(country)
            , m_location(location)
            , m_population(population)
            {
                
            }
            
            SdkModel::SearchResultModel GeoNamesSearchResultDto::ToSearchResultModel() const
            {
                SdkModel::SearchResultModel model(SdkModel::SearchResultModel::CurrentVersion,
                                                  "",
                                                  m_name,
                                                  Eegeo::Space::LatLong::FromDegrees(m_location.GetLatitudeInDegrees(),
                                                                                     m_location.GetLongitudeInDegrees()),
                                                  0,
                                                  false,
                                                  "",
                                                  0,
                                                  "",
                                                  m_country,
                                                  "",
                                                  "",
                                                  std::vector<std::string>(),
                                                  "",
                                                  "GeoNames",
                                                  "",
                                                  "",
                                                  std::vector<std::string>(),
                                                  0,
                                                  Eegeo::Helpers::Time::MillisecondsSinceEpoch());
                
                return model;
            }
        }
    }
}
