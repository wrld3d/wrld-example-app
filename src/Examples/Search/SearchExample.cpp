//
//  SearchExample.cpp
//  ExampleApp
//
//  Created by Scott on 18/06/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#include "SearchExample.h"
#include "PoiSearchResult.h"
#include "IInterestPointProvider.h"

using namespace Examples;
using namespace Eegeo::Space;
using namespace Eegeo::Search::Service;

SearchExample::SearchExample(Eegeo::Search::Service::SearchService& searchService,
                             Eegeo::Location::IInterestPointProvider& interestPointProvider)
:searchService(searchService)
,interestPointProvider(interestPointProvider)
{
}

void SearchExample::Start()
{
    const std::string query = "Transamerica Pyramid";
    const bool isCategory = false;
    const LatLongAltitude where = LatLongAltitude::FromECEF(interestPointProvider.GetEcefInterestPoint());
    Eegeo::Search::Service::IPoiSearchCallback& callback = *this;
    
    Eegeo_TTY("Attempting to search for %s at (%f, %f)!\n",
              query.c_str(),
              where.GetLatitudeInDegrees(),
              where.GetLongitudeInDegrees());
    
    SearchQueryResult::Value result = searchService.SearchForPoi(query, isCategory, where, callback);
    
    if(result != SearchQueryResult::OK)
    {
        Eegeo_TTY("Attempt to search for %s POI failed!\n", query.c_str());
    }
}

void SearchExample::HandlePoiSearchResults(const Eegeo::Search::Service::PoiSearchResult& result)
{
    if(result.success)
    {
        for(std::vector<PoiSearchEntry>::const_iterator it = result.entries.begin();
            it != result.entries.end();
            ++ it)
        {
            const PoiSearchEntry& entry = *it;
            
            Eegeo_TTY("Search discovered place with name %s and place ID %s at (%f, %f)\n",
                      entry.name.c_str(),
                      entry.placeId.c_str(),
                      entry.location.GetLatitudeInDegrees(),
                      entry.location.GetLongitudeInDegrees());
        }
    }
    else
    {
        Eegeo_TTY("Search failed!\n");
    }
}