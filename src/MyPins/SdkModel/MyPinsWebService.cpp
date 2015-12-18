// Copyright (c) 2015 eeGeo. All rights reserved.

#include "MyPinsWebService.h"
#include "MyPinModel.h"
#include "LatLongAltitude.h"
#include "MyPinsHelpers.h"
#include "SearchResultModel.h"

#include "IWebLoadRequestFactory.h"
#include "IWebLoadRequest.h"

#include "IFileIO.h"
#include <fstream>

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            MyPinsWebService::MyPinsWebService(
                                               const std::string& webServiceBaseUrl,
                                               const std::string& webServiceAuthToken,
                                               Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory,
                                               Eegeo::Helpers::IFileIO& fileIO)
            : m_url(webServiceBaseUrl)
            , m_authHeader("Token " + webServiceAuthToken)
            , m_webLoadRequestFactory(webLoadRequestFactory)
            , m_fileIO(fileIO)
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
                const Eegeo::Space::LatLong& latLong = pinModel.GetLatLong();
                
                m_webLoadRequestFactory.Begin(Eegeo::Web::HttpVerbs::POST, m_url + CreatePoiEndPoint, m_webRequestCompleteCallback)
                    .AddFormData("poi[latitude]", ConvertModelDetailToString(latLong.GetLatitudeInDegrees()))
                    .AddFormData("poi[longitude]", ConvertModelDetailToString(latLong.GetLongitudeInDegrees()))
                    .AddFormData("poi[type]", PoiTypeSearchResult)
                    .AddFormData("poi[vendor_name]", searchResult.GetIdentifier())
                    .AddFormData("poi[interior_id]", searchResult.GetBuildingId().Value())
                    .AddFormData("poi[interior_floor_number]", ConvertModelDetailToString(searchResult.GetFloor()))
                    .AddHeader("Authorization", m_authHeader)
                    .Build()->Load();
            }
            
            void MyPinsWebService::SubmitUserCreatedPin(
                                                        const MyPinModel& pinModel,
                                                        const std::string& imagePath)
            {
                std::map<std::string, std::string> formData;
                SetLatLongFormData(pinModel, formData);
                
                const Eegeo::Space::LatLong& latLong = pinModel.GetLatLong();
                
                Eegeo::Web::WebRequestBuilder resquestBuilder = m_webLoadRequestFactory.Begin(Eegeo::Web::HttpVerbs::POST, m_url + CreatePoiEndPoint, m_webRequestCompleteCallback)
                    .AddFormData("poi[latitude]", ConvertModelDetailToString(latLong.GetLatitudeInDegrees()))
                    .AddFormData("poi[longitude]", ConvertModelDetailToString(latLong.GetLongitudeInDegrees()))
                    .AddFormData("poi[type]", PoiTypeUserGenerated)
                    .AddFormData("poi[interior_id]", pinModel.GetBuildingId().Value())
                    .AddFormData("poi[interior_floor_number]", ConvertModelDetailToString(pinModel.GetFloor()))
                    .AddHeader("Authorization", m_authHeader);
                
                const bool hasImage = !imagePath.empty();
                
                //std::map<std::string, Eegeo::Web::ImageUploadData> imageData;
                if (hasImage)
                {
                    std::vector<Byte> imageDataBytes;
                    std::fstream stream;
                    size_t size;
                    if(m_fileIO.OpenFile(stream, size, imagePath, std::ios::in | std::ios::binary))
                    {
                        imageDataBytes.resize(size);
                        stream.read((char*)&imageDataBytes[0], size);
                    }
                    else
                    {
                        Eegeo_TTY("Failed to open file for pin image");
                    }
                    
                    const Eegeo::Web::WebPostData imagePostData = Eegeo::Web::WebPostData::CreateBufferData(imagePath, imageDataBytes);
                    resquestBuilder.AddPostData("poi[image]", imagePostData);
                }
                
                resquestBuilder.Build()->Load();
            }
            
            void MyPinsWebService::WebRequestCompleteCallback(Eegeo::Web::IWebResponse& webResponse)
            {
                Eegeo_TTY("Web Request Completed, code: %d url: %s\n", webResponse.GetHttpStatusCode(), webResponse.GetUrl().c_str());
            }
        }
    }
}