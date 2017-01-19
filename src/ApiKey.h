// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    //! defines a path to the app config file, which is used to provide the EegeoApiKey and other credentials
    static const std::string ApplicationConfigurationPath = "ApplicationConfigs/standard_config.json";

    //! REQUIRED: You must obtain an API key for the eeGeo SDK from https://www.eegeo.com/developers/ and set is as the value of "EegeoApiKey" in the config file
    
    //! Optional: If 'useYelp' is true in AppHost you may wish to obtain a Yelp API key from https://www.yelp.com/developers for POI search provision.
    //! If so, set credentials using the following keys in the app config file:
    //! YelpConsumerKey
    //! YelpConsumerSecret
    //! YelpOAuthToken
    //! YelpOAuthTokenSecret
    //! Optional: You may wish to obtain a geonames account key from http://www.geonames.org/export/web-services.html for address/place search provision.
    //! Set it as the value of 'GeoNamesUserName' in the app config file:
 
    //! Optional: You may wish to obtain an API key for Flurry from https://developer.yahoo.com/analytics/ for metrics.
    //! Set it as the value of 'FlurryApiKey' in the app config file:
}
