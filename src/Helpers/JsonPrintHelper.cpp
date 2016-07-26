// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "JsonPrintHelper.h"

#include "stringbuffer.h"
#include "prettywriter.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace JsonPrintHelpers
        {
            std::string JsonToPrettyString(const rapidjson::Value& json)
            {
                rapidjson::StringBuffer buffer;
                rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
                json.Accept(writer);
                return std::string(buffer.GetString());
            }
        }
    }
}
