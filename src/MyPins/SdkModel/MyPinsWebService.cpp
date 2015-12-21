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
                
                void SetLatLongFormData(const MyPinModel& pinModel, Eegeo::Web::WebRequestBuilder& requestBuilder)
                {
                    const Eegeo::Space::LatLong& latLong = pinModel.GetLatLong();
                    const std::string& latitude = ConvertModelDetailToString(latLong.GetLatitudeInDegrees());
                    const std::string& longitude = ConvertModelDetailToString(latLong.GetLongitudeInDegrees());
                    requestBuilder.AddFormData("poi[latitude]", latitude);
                    requestBuilder.AddFormData("poi[longitude]", longitude);
                }
            }
            
            void MyPinsWebService::SubmitSearchResultPin(
                                                         const MyPinModel& pinModel,
                                                         const Search::SdkModel::SearchResultModel& searchResult)
            {
                // when storing search result pins, due to licensing terms we're just storing the lat, long and id
                // this allows us to refresh the pin when required.
                Eegeo::Web::WebRequestBuilder requestBuilder = m_webLoadRequestFactory.Begin(Eegeo::Web::HttpVerbs::POST, m_url + CreatePoiEndPoint, m_webRequestCompleteCallback)
                    .AddFormData("poi[type]", PoiTypeSearchResult)
                    .AddFormData("poi[vendor_name]", searchResult.GetVendor())
                    .AddFormData("poi[vendor_id]", searchResult.GetIdentifier())
                    .AddFormData("poi[interior_id]", searchResult.GetBuildingId().Value())
                    .AddFormData("poi[interior_floor_number]", ConvertModelDetailToString(searchResult.GetFloor()))
                    .AddHeader("Authorization", m_authHeader);
                
                SetLatLongFormData(pinModel, requestBuilder);
                
                requestBuilder.Build()->Load();
            }
            
            void MyPinsWebService::SubmitUserCreatedPin(
                                                        const MyPinModel& pinModel,
                                                        const std::string& imagePath)
            {
                Eegeo::Web::WebRequestBuilder requestBuilder = m_webLoadRequestFactory.Begin(Eegeo::Web::HttpVerbs::POST, m_url + CreatePoiEndPoint, m_webRequestCompleteCallback)
                    .AddFormData("poi[type]", PoiTypeUserGenerated)
                    .AddFormData("poi[title]", pinModel.GetTitle())
                    .AddFormData("poi[description]", pinModel.GetDescription())
                    .AddFormData("poi[interior_id]", pinModel.GetBuildingId().Value())
                    .AddFormData("poi[interior_floor_number]", ConvertModelDetailToString(pinModel.GetFloor()))
                    //                    .AddPostData()
                    .AddHeader("Authorization", m_authHeader);

                SetLatLongFormData(pinModel, requestBuilder);

                const bool hasImage = !imagePath.empty();

                if (hasImage)
                {
                    std::vector<Byte> imageData;
                    std::fstream stream;
                    size_t size;

                    if (m_fileIO.OpenFile(stream, size, imagePath, std::ios::in | std::ios::binary))
                    {
                        imageData.resize(size);
                        stream.read((char*)&imageData[0], size);
                    }
                    else
                    {
                        Eegeo_TTY("Failed to open file for pin image");
                    }

                    const Eegeo::Web::WebPostData imagePostData = Eegeo::Web::WebPostData::CreateBufferData("pin_image.jpg", imageData);
                    requestBuilder.AddPostData("poi[image]", imagePostData);
                }

                requestBuilder.Build()->Load();
            }
            
            void MyPinsWebService::WebRequestCompleteCallback(Eegeo::Web::IWebResponse& webResponse)
            {
                size_t resultSize = webResponse.GetBodyData().size();
                std::string responseString = resultSize > 0 ? std::string(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize) : "<empty>";
                Eegeo_TTY("Web Request Completed, code: %d response: %s\n", webResponse.GetHttpStatusCode(), responseString.c_str());
            }
        }
    }
}