// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "SearchResultModel.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace Helpers
        {
            namespace
            {
                std::vector<std::string> ParseDeskIds(const std::string& jsonData);

                std::pair<std::string, std::size_t> GetBuildingFromId(const std::string& deskId);

                std::string GetFloorFromId(const std::string& deskId, std::size_t buildingPos);

                std::map<std::string, std::map<std::string, std::size_t> > GetBuildingToFloorDeskNumMapping(const std::vector<std::string>& deskIds);

                std::string GetFormattedMapping(const std::map<std::string, std::map<std::string, std::size_t> >& mapping);
            }

            std::string GetFormattedFloorRanges(const std::string& jsonData);
        }
    }
}
