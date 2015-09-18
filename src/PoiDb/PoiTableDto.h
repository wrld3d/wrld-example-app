// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiDb.h"

#include <string>


namespace ExampleApp
{
    namespace PoiDb
    {
        struct PoiTableDto
        {
            int poi_id;
            std::string name;
            std::string job_title;
            std::string image_filename;
            std::string working_group;
            std::string office_location;
            std::string desk_code;
            std::string interior_id;
            int interior_floor;
            double latitude_degrees;
            double longitude_degrees;
            
            PoiTableDto()
            : poi_id(0)
            , interior_floor(0)
            , latitude_degrees(0.0)
            , longitude_degrees(0.0)
            {
                
            }
        };
    }
}
