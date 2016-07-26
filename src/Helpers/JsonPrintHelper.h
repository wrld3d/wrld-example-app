// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "document.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace JsonPrintHelpers
        {
            std::string JsonToPrettyString(const rapidjson::Value& json);
        }
    }
}
