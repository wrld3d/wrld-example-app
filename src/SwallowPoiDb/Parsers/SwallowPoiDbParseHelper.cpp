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
        }
    }
}