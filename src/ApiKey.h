// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    //! REQUIRED: You must obtain an API key for the eeGeo SDK from https://www.eegeo.com/developers/
    static const std::string ApiKey = "bd23b6d0699b090d315527ababedacb7";
    
    //! Optional: If 'useYelp' is true in AppHost you may wish to obtain a Yelp API key from https://www.yelp.com/developers for POI search provision
    static const std::string YelpConsumerKey = "8_4FTFD1k-bOhMv6bCIZEw";
    static const std::string YelpConsumerSecret = "ZhCAoLI9bbDALeXMw-FUTZOCAug";
    static const std::string YelpOAuthToken = "cNBh0p1tGXTKVt-Pf6b-Z3uX8zlpNWjq";
    static const std::string YelpOAuthTokenSecret = "bYe9r5miUuwm87HcMnt3ZMng9aU";
    
    //! Optional: You may wish to obtain a geonames account key from http://www.geonames.org/export/web-services.html for address/place search provision
    static const std::string GeoNamesUserName = "eegeo_bloomberg_ios";
    
    //! Optional: If 'useYelp' is false in AppHost you may wish to obtain a Decarta API key from http://www.decarta.com/ for POI search provision
    static const std::string DecartaApiKey = "OBTAIN DECARTA SEARCH KEY AND INSERT IT HERE";
    
    //! Optional: You may wish to obtain an API key for Flurry from https://developer.yahoo.com/analytics/ for metrics
    static const std::string FlurryApiKey = "OBTAIN FLURRY KEY AND INSERT IT HERE";
}
