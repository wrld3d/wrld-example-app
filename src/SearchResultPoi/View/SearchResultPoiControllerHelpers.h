// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "SearchResultModel.h"
#include "ICallback.h"
#include <string>
#include <map>
#include "document.h"
#include "TimeHelpers.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace Helpers
        {
            std::string GetFormattedFloorRanges(const std::string& jsonData);
        }
    }
}
