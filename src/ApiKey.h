// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    static const std::string ApplicationConfigurationPath = "ApplicationConfigs/standard_config.json";
    
    //! REQUIRED: You must obtain an API key for the eeGeo SDK from https://www.eegeo.com/developers/
    static const std::string ApiKey = "";
    
    //! Optional: If 'useYelp' is true in AppHost you may wish to obtain a Yelp API key from https://www.yelp.com/developers for POI search provision
    static const std::string YelpConsumerKey = "quNfQ8G7oxtR8gPfWsLWCQ";
    static const std::string YelpConsumerSecret = "RTXEUQaCv-8-TZNc1G1wGUATHuY";
    static const std::string YelpOAuthToken = "p3tWrLAa7C6QzC7OVHWFb3mIacwidWj6";
    static const std::string YelpOAuthTokenSecret = "Eqrvmumb9HGZ0_8CHPNiEETmN-s";
    
    //! Optional: You may wish to obtain a geonames account key from http://www.geonames.org/export/web-services.html for address/place search provision
    static const std::string GeoNamesUserName = "OBTAIN GEONAMES USERNAME AND INSERT IT HERE";
 
    //! Optional: You may wish to obtain an API key for Flurry from https://developer.yahoo.com/analytics/ for metrics
    static const std::string FlurryApiKey = "OBTAIN FLURRY KEY AND INSERT IT HERE";

    //! Optional: You may wish to obtain twitter bearer token. Check https://dev.twitter.com/oauth/application-only for instructions
    static const std::string TwitterAuthCode = "INSERT TWITTER AUTH CODE HERE";
    
}
