// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            /*
                Version 1: Initial version
                Version 2: Added optional ratings image & reviews count data (8/7/15)
                Version 3: Added storing of pin vendor data, if pin predates this version it should proably use Yelp as vendor (3/12/15)
                Version 4: Add "pinIconKey", deprecate "icon" (SdkMapPinIconIndex)
             */
            const int MyPinModel::CurrentVersion = 4;
            
            MyPinModel::MyPinModel()
                : m_version(-1)
                , m_modelId(-1)
                , m_reviewCount(0)
                , m_latLong(0.0, 0.0)
                , m_heightAboveTerrainMetres(0.f)
                , m_interior(false)
                , m_buildingId("")
                , m_floor(0)
            {

            }

            MyPinModel::MyPinModel(int version,
                                   int modelId,
                                   const std::string& title,
                                   const std::string& description,
                                   const std::string& vendor,
                                   const std::string& ratingsImage,
                                   const std::string& pinIconKey,
                                   int reviewCount,
                                   const Eegeo::Space::LatLong& latLong,
                                   float heightAboveTerrainMetres,
                                   bool interior,
                                   const Eegeo::Resources::Interiors::InteriorId& buildingId,
                                   int floor)
            : m_version(version)
            , m_modelId(modelId)
            , m_title(title)
            , m_description(description)
            , m_vendor(vendor)
            , m_ratingsImage(ratingsImage)
            , m_pinIconKey(pinIconKey)
            , m_reviewCount(reviewCount)
            , m_latLong(latLong)
            , m_heightAboveTerrainMetres(heightAboveTerrainMetres)
            , m_interior(interior)
            , m_buildingId(buildingId)
            , m_floor(floor)
            {
                
            }
        }
    }
}
