// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourAddedObserver.h"
#include "ITourRepository.h"
#include "IWorldPinsService.h"
#include "TourWorldPinSelectionHandler.h"
#include "WorldPinItemModel.h"
#include "WorldPinVisibility.h"
#include "SearchVendorNames.h"
#include "ColorHelpers.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            
            namespace
            {
                const std::string GenerateTourHovercardJsonData(const TourModel& tourModel)
                {
                    const Helpers::ColorHelpers::Color& baseColor = tourModel.HoverCardBaseColor();
                    const Helpers::ColorHelpers::Color& textColor = tourModel.HoverCardTextColor();
                    
                    rapidjson::Document jsonDoc;
                    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                    rapidjson::Value valueObject(rapidjson::kObjectType);
                    rapidjson::Value baseColorObject(rapidjson::kObjectType);
                    rapidjson::Value textColorObject(rapidjson::kObjectType);
                    std::string jsonString ="";
                    
                    baseColorObject.AddMember("r", static_cast<int>(baseColor.GetRed()), allocator);
                    baseColorObject.AddMember("g", static_cast<int>(baseColor.GetGreen()), allocator);
                    baseColorObject.AddMember("b", static_cast<int>(baseColor.GetBlue()), allocator);
                    
                    textColorObject.AddMember("r", static_cast<int>(textColor.GetRed()), allocator);
                    textColorObject.AddMember("g", static_cast<int>(textColor.GetGreen()), allocator);
                    textColorObject.AddMember("b", static_cast<int>(textColor.GetBlue()), allocator);
                    
                    valueObject.AddMember("base_col", baseColorObject, allocator);
                    valueObject.AddMember("text_col", textColorObject, allocator);
                    
                    rapidjson::StringBuffer strbuf;
                    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                    valueObject.Accept(writer);
                    return strbuf.GetString();
                }
            }
            
            TourAddedObserver::TourAddedObserver(ITourRepository& tourRepository,
                                                 WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                 TourWorldPinSelectionHandlerFactory& tourWorldPinSelectionHandlerFactory)
            : m_tourRepository(tourRepository)
            , m_worldPinsService(worldPinsService)
            , m_tourWorldPinSelectionHandlerFactory(tourWorldPinSelectionHandlerFactory)
            , m_binding(this, &TourAddedObserver::HandleTourAdded)
            {
                m_tourRepository.InsertItemAddedCallback(m_binding);
            }
            
            TourAddedObserver::~TourAddedObserver()
            {
                m_tourRepository.RemoveItemAddedCallback(m_binding);
            }
            
            void TourAddedObserver::HandleTourAdded(TourModel& tourModel)
            {
                typedef WorldPins::SdkModel::WorldPinItemModel TPin;
                const int IconIndex = 10;
                const std::string tourVendor = tourModel.UsesTwitter()? Search::WorldTwitterVendorName : Search::ExampleTourVendorName;
                TPin* pPin = m_worldPinsService.AddPin(m_tourWorldPinSelectionHandlerFactory.CreateSelectionHandler(tourModel),
                                                       NULL,
                                                       WorldPins::SdkModel::WorldPinFocusData(tourModel.Name(),
                                                                                              tourModel.IntroText(),
                                                                                              tourVendor,
                                                                                              GenerateTourHovercardJsonData(tourModel),
                                                                                              "",
                                                                                              0),
                                                       tourModel.IsInterior(),
                                                       tourModel.WorldPinInteriorData(),
                                                       tourModel.Location(),
                                                       tourModel.IconIndex(),
                                                       0.0f,
                                                       WorldPins::SdkModel::WorldPinVisibility::World);
                
                pPin->SetFocusable(true); // Added to stop unused variable warning. May also prove useful in future to set focusable from tourModel
                
                // map pPin to tourModel somehow, possibly in TourService or another repo.
            }
        }
    }
}
