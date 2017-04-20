// Copyright (c) 2015 eeGeo. All rights reserved.

#include "MyPinsWebService.h"
#include "MyPinModel.h"
#include "LatLongAltitude.h"
#include "MyPinsHelpers.h"
#include "SearchResultModel.h"

#include "IWebLoadRequestFactory.h"
#include "IWebLoadRequest.h"
#include "WebPostData.h"

#include <fstream>

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            MyPinsWebService::MyPinsWebService(
                                               const std::string& myPinsWebServiceBaseUrl,
                                               const std::string& myPinsWebServiceAuthToken,
                                               const std::string& myPinsPoiSetId,
                                               Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory)
            : m_url(myPinsWebServiceBaseUrl)
            , m_myPinsWebServiceAuthToken(myPinsWebServiceAuthToken)
            , m_myPinsPoiSetId(myPinsPoiSetId)
            , m_webLoadRequestFactory(webLoadRequestFactory)
            , m_webRequestCompleteCallback(this, &MyPinsWebService::WebRequestCompleteCallback)
            {
                
            }
            
            namespace
            {
                const std::string PoiEndPoint = "/pois/";
            }
            
            void MyPinsWebService::SubmitUserCreatedPin(
                                                        const MyPinModel& pinModel)
            {
                std::string poiServiceUrl = CreatePoiServiceUrl();
                const std::string postData = CreatePinPostData(pinModel);
                
                
                Eegeo::Web::WebRequestBuilder requestBuilder = m_webLoadRequestFactory.Begin(Eegeo::Web::HttpVerbs::POST, poiServiceUrl, m_webRequestCompleteCallback).SetPostBodyData(Eegeo::Web::WebPostData::CreateTextData(postData));

                requestBuilder.Build()->Load();
            }
            
            void MyPinsWebService::WebRequestCompleteCallback(Eegeo::Web::IWebResponse& webResponse)
            {
                size_t resultSize = webResponse.GetBodyData().size();
                std::string responseString = resultSize > 0 ? std::string(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize) : "<empty>";
                Eegeo_TTY("Web Request Completed, code: %d response: %s\n", webResponse.GetHttpStatusCode(), responseString.c_str());
            }
            
            const std::string MyPinsWebService::CreatePoiServiceUrl()
            {
                return m_url + "/" + m_myPinsPoiSetId + PoiEndPoint + "?token=" + m_myPinsWebServiceAuthToken;
            }
            
            const char * const BoolToString(bool b)
            {
                return b ? "true" : "false";
            }
            
            const std::string MyPinsWebService::CreatePinPostData(const MyPinModel& pinModel)
            {
                std::string json = "";
                if(pinModel.IsInterior())
                {
                    json = "{\n  \"title\":\"" + pinModel.GetTitle()
                    + "\",\n  \"subtitle\":\"\",\n  \"tags\":\"office business\",\n  \"lat\":\"" + ConvertModelDetailToString(pinModel.GetLatLong().GetLatitudeInDegrees())
                    + "\",\n  \"lon\":\"" + ConvertModelDetailToString(pinModel.GetLatLong().GetLongitudeInDegrees())
                    + "\",\n  \"indoor\":\"" + BoolToString(pinModel.IsInterior())
                    + "\",\n  \"indoor_id\":\"" + pinModel.GetBuildingId().Value()
                    + "\",\n  \"floor_id\":\"" + ConvertModelDetailToString(pinModel.GetFloor())
                    + "\",\n \"user_data\":{\"description\":\"" + pinModel.GetDescription() + "\"}}";
                }
                else
                {
                    json = "{\n  \"title\":\"" + pinModel.GetTitle()
                    + "\",\n  \"subtitle\":\"\",\n  \"tags\":\"office business\",\n  \"lat\":\"" + ConvertModelDetailToString(pinModel.GetLatLong().GetLatitudeInDegrees())
                    + "\",\n  \"lon\":\"" + ConvertModelDetailToString(pinModel.GetLatLong().GetLongitudeInDegrees())
                    + "\",\n \"user_data\":{\"description\":\"" + pinModel.GetDescription() + "\"}}";
                }
                return json;
            }
        }
    }
}
