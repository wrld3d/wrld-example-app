// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "document.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        namespace Parsers
        {
            enum FtsColumnIndices
            {
                fts_row_id = 0,
                fts_snippet,
                fts_offsets,
                FtsQueryColumnIndices_MAX
            };
            
            std::string GetImageUrl(const std::string& assetsBaseUrl, const std::string& rawImageFilenameField);

			void AddStringToJson(const std::string& name, const std::string& value, rapidjson::Document::AllocatorType& allocator, rapidjson::Value& out_jsonValue);
        }
    }
}