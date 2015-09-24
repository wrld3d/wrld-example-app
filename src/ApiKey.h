// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    //! REQUIRED: You must obtain an API key for the eeGeo SDK from https://www.eegeo.com/developers/
    static const std::string ApiKey = "d6811a033724b916ae875aad3da4d39d";
    
    //! Optional: If 'useYelp' is true in AppHost you may wish to obtain a Yelp API key from https://www.yelp.com/developers for POI search provision
    static const std::string YelpConsumerKey = "5XCRjDihxFzymofV7c026A";
    static const std::string YelpConsumerSecret = "CypX2XlLek_a_PucVQabUotTM0c";
    static const std::string YelpOAuthToken = "P7dxJs2lhwwwPgy9jSDyY7AGm78G8eoR";
    static const std::string YelpOAuthTokenSecret = "NfNAVynMkDUAylvV4LKNl6EWhDY";
    
    //! Optional: You may wish to obtain a geonames account key from http://www.geonames.org/export/web-services.html for address/place search provision
    static const std::string GeoNamesUserName = "Eegeo_Cisco";
    
    //! Optional: You may wish to obtain an API key for Flurry from https://developer.yahoo.com/analytics/ for metrics
    static const std::string FlurryApiKey = "OBTAIN FLURRY KEY AND INSERT IT HERE";
}
