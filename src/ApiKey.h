// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    //! REQUIRED: You must obtain an API key for the eeGeo SDK from https://www.eegeo.com/developers/
    static const std::string ApiKey = "OBTAIN API_KEY FROM https://www.eegeo.com/developers/ AND INSERT IT HERE";
    
    //! Optional: If 'useYelp' is true in AppHost you may wish to obtain a Yelp API key from https://www.yelp.com/developers for POI search provision
    static const std::string YelpConsumerKey = "OBTAIN YELP CONSUMER KEY AND INSERT IT HERE";
    static const std::string YelpConsumerSecret = "OBTAIN YELP CONSUMER SECRET AND INSERT IT HERE";
    static const std::string YelpOAuthToken = "OBTAIN YELP OAUTH TOKEN AND INSERT IT HERE";
    static const std::string YelpOAuthTokenSecret = "OBTAIN YELP OAUTH TOKEN SECRET AND INSERT IT HERE";
    
    //! Optional: You may wish to obtain a geonames account key from http://www.geonames.org/export/web-services.html for address/place search provision
    static const std::string GeoNamesUserName = "OBTAIN GEONAMES USERNAME AND INSERT IT HERE";
 
    //! Optional: You may wish to obtain an API key for Flurry from https://developer.yahoo.com/analytics/ for metrics
    static const std::string FlurryApiKey = "OBTAIN FLURRY KEY AND INSERT IT HERE";
}
