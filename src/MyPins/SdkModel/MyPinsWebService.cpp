// Copyright (c) 2015 eeGeo. All rights reserved.

#include "MyPinsWebService.h"
#include "MyPinModel.h"
#include "LatLongAltitude.h"
#include "MyPinsHelpers.h"
#include "SearchResultModel.h"

#include "IWebLoadRequestFactory.h"
#include "IWebLoadRequest.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            MyPinsWebService::MyPinsWebService(
                                               const std::string& webServiceBaseUrl,
                                               const std::string& webServiceAuthToken,
                                               Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory)
            : m_url(webServiceBaseUrl)
            , m_authHeader("Token " + webServiceAuthToken)
            , m_webLoadRequestFactory(webLoadRequestFactory)
            , m_webRequestCompleteCallback(this, &MyPinsWebService::WebRequestCompleteCallback)
            {
                
            }
            
            namespace
            {
                const std::string CreatePoiEndPoint = "/pois/new";
                
                const std::string PoiTypeSearchResult = "SearchResultPoi";
                const std::string PoiTypeUserGenerated = "UserGeneratedPoi";
                
                void SetLatLongFormData(const MyPinModel& pinModel, std::map<std::string, std::string>& out_formData)
                {
                    const Eegeo::Space::LatLong& latLong = pinModel.GetLatLong();
                    out_formData["poi[latitude]"] = ConvertModelDetailToString(latLong.GetLatitudeInDegrees());
                    out_formData["poi[longitude]"] = ConvertModelDetailToString(latLong.GetLongitudeInDegrees());
                }
            }
            
            void MyPinsWebService::SubmitSearchResultPin(
                                                         const MyPinModel& pinModel,
                                                         const Search::SdkModel::SearchResultModel& searchResult)
            {
                std::map<std::string, std::string> formData;
                SetLatLongFormData(pinModel, formData);
                
                // when storing search result pins, due to licensing terms we're just storing the lat, long and id
                // this allows us to refresh the pin when required.
                formData["poi[type]"] = PoiTypeSearchResult;
                
                formData["poi[vendor_name]"] = searchResult.GetVendor();
                formData["poi[vendor_id]"] = searchResult.GetIdentifier();
                
                std::map<std::string, std::string> headerData;
                headerData["Authorization"] = m_authHeader;
                
                m_webLoadRequestFactory.CreatePost(m_url + CreatePoiEndPoint,
                                                   m_webRequestCompleteCallback,
                                                   NULL,
                                                   formData,
                                                   headerData)->Load();
            }
            
            void MyPinsWebService::SubmitUserCreatedPin(
                                                        const MyPinModel& pinModel,
                                                        const std::string& imagePath)
            {
                std::map<std::string, std::string> formData;
                SetLatLongFormData(pinModel, formData);
                
                formData["poi[type]"] = PoiTypeUserGenerated;
                
                formData["poi[title]"] = pinModel.GetTitle();
                formData["poi[description]"] = pinModel.GetDescription();
                
                const bool hasImage = !imagePath.empty();
                
                std::map<std::string, Eegeo::Web::ImageUploadData> imageData;
                if (hasImage)
                {
                    Eegeo::Web::ImageUploadData imageUpload(imagePath, "pin_image.jpg", Eegeo::Web::ImageUploadData::JPEG);
                    imageData["poi[image]"] = imageUpload;
                }
                
                std::map<std::string, std::string> headerData;
                headerData["Authorization"] = m_authHeader;
                
                m_webLoadRequestFactory.CreatePost(m_url + CreatePoiEndPoint,
                                                   m_webRequestCompleteCallback,
                                                   NULL,
                                                   formData,
                                                   headerData,
                                                   imageData)->Load();
            }
            
            void MyPinsWebService::WebRequestCompleteCallback(Eegeo::Web::IWebLoadRequest& webLoadRequest)
            {
                size_t resultSize = webLoadRequest.GetResourceData().size();
                std::string responseString = std::string(reinterpret_cast<char const*>(&(webLoadRequest.GetResourceData().front())), resultSize);
                Eegeo_TTY("Web Request Completed, code: %d response: %s\n", webLoadRequest.HttpStatusCode(), responseString.c_str());
            }
        }
    }
}