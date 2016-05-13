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
                std::vector<std::string> ParseDeskIds(const std::string& jsonData)
                {
                    std::vector<std::string> deskIds;

                    rapidjson::Document document;

                    if (document.Parse<0>(jsonData.c_str()).HasParseError())
                    {
                        return deskIds;
                    }

                    const std::string desks("desks");

                    if (!document.HasMember(desks.c_str()))
                    {
                        return deskIds;
                    }

                    if (!document[desks.c_str()].IsArray())
                    {
                        return deskIds;
                    }

                    rapidjson::Value& membersObject = document[desks.c_str()];

                    if (!membersObject.IsArray())
                    {
                        return deskIds;
                    }

                    for (rapidjson::Value::ValueIterator iter = membersObject.Begin();
                        iter != membersObject.End();
                        ++iter)
                    {
                        deskIds.push_back(iter->GetString());
                    }

                    return deskIds;
                }

                std::pair<std::string, std::size_t> GetBuildingFromId(const std::string& deskId)
                {
                    const int BUILDINGS_NUM = 4;
                    std::string swallowBuildingCodes[BUILDINGS_NUM] = { "38FS", "FS", "CG", "PKH" };
                    std::string swallowBuildingNames[BUILDINGS_NUM] = { "38 Finsbury", "50 Finsbury", "City Gate House", "Park House" };

                    for (std::size_t i = 0; i < BUILDINGS_NUM; ++i)
                    {
                        std::size_t pos = deskId.find(swallowBuildingCodes[i]);

                        if (pos != std::string::npos)
                        {
                            return std::make_pair(swallowBuildingNames[i], pos + swallowBuildingCodes[i].length());
                        }
                    }

                    return std::make_pair(std::string(), std::string::npos);
                }

                std::string GetFloorFromId(const std::string& deskId, std::size_t buildingPos)
                {
                    const std::string& floorDeskCode = deskId.substr(buildingPos);

                    std::string currentFloor;

                    //search for the second trailing '-' which is consistent across all
                    //desk codes, skip the first in case it contains a '-'
                    std::size_t floorNumPos = floorDeskCode.find('-', 1);

                    if (floorDeskCode[0] == '-')
                    {
                        //Certain desk codes may or may not have a '-' after the building code
                        //so we need to factor it out if it exists.
                        currentFloor += floorDeskCode.substr(1, floorNumPos - 1);
                    }
                    else
                    {
                        currentFloor += floorDeskCode.substr(0, floorNumPos);
                    }

                    return currentFloor;
                }

                std::map<std::string, std::map<std::string, std::size_t> > GetBuildingToFloorDeskNumMapping(const std::vector<std::string>& deskIds)
                {
                    std::map<std::string, std::map<std::string, std::size_t> > buildingsToFloorDeskMap;

                    for (std::vector<std::string>::const_iterator it = deskIds.begin();
                        it != deskIds.end();
                        it++)
                    {
                        const std::pair<std::string, std::size_t>& building = GetBuildingFromId(*it);

                        if (building.second == std::string::npos)
                        {
                            continue;
                        }

                        const std::string& floor = GetFloorFromId(*it, building.second);

                        std::map<std::string, std::map<std::string, std::size_t> >::iterator buildingKey = buildingsToFloorDeskMap.find(building.first);

                        if (buildingKey != buildingsToFloorDeskMap.end())
                        {
                            std::map<std::string, std::size_t>& floorToDeskMap = buildingKey->second;
                            std::map<std::string, std::size_t>::iterator floorKey = floorToDeskMap.find(floor);

                            if (floorKey != floorToDeskMap.end())
                            {
                                ++floorKey->second;
                            }
                            else
                            {
                                floorToDeskMap.insert(std::make_pair(floor, 1));
                            }
                        }
                        else
                        {
                            std::map<std::string, std::size_t> floorToDeskNumMapping;
                            floorToDeskNumMapping.insert(std::make_pair(floor, 1));

                            buildingsToFloorDeskMap.insert(std::make_pair(building.first, floorToDeskNumMapping));
                        }
                    }

                    return buildingsToFloorDeskMap;
                }

                std::string GetFormattedMapping(const std::map<std::string, std::map<std::string, std::size_t> >& mapping)
                {
                    std::stringstream formattedMapping;

                    for (std::map<std::string, std::map<std::string, std::size_t> >::const_iterator building = mapping.begin();
                        building != mapping.end();
                        ++building)
                    {
                        formattedMapping << building->first << "\n";

                        const std::map<std::string, std::size_t>& floorMapping = building->second;

                        for (std::map<std::string, std::size_t>::const_iterator floor = floorMapping.begin();
                            floor != floorMapping.end();
                            ++floor)
                        {
                            formattedMapping << "Floor " << floor->first << ": " << floor->second << "\n";
                        }

                        if (!floorMapping.empty())
                        {
                            formattedMapping << "\n";
                        }
                    }

                    return formattedMapping.str();
                }
            }

            std::string GetFormattedFloorRanges(const std::string& jsonData)
            {
                std::string floorRangeInfo;

                const std::vector<std::string>& deskIds = ParseDeskIds(jsonData);

                if (deskIds.empty())
                {
                    return floorRangeInfo;
                }

                const std::map<std::string, std::map<std::string, std::size_t> >& mapping = GetBuildingToFloorDeskNumMapping(deskIds);

                floorRangeInfo = GetFormattedMapping(mapping);

                return floorRangeInfo;
            }
        }
    }
}
