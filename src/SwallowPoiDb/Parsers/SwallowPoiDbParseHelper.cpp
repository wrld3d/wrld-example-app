// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SwallowPoiDbParseHelper.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        namespace Parsers
        {
            std::string GetImageUrl(const std::string& assetsBaseUrl, const std::string& rawImageFilenameField)
            {
                return rawImageFilenameField.empty() ? std::string() : assetsBaseUrl + rawImageFilenameField;
            }

			void AddStringToJson(const std::string& name, const std::string& value, rapidjson::Document::AllocatorType& allocator, rapidjson::Value& out_jsonValue)
			{
				rapidjson::Value resultValue(rapidjson::kStringType);

				resultValue.SetString(value.c_str(), value.size(), allocator);

				out_jsonValue.AddMember(name.c_str(),
					resultValue,
					allocator);
			}
        }
    }
}