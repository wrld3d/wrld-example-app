// Copyright eeGeo Ltd (2012-2018), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "Interiors.h"

#include <string>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace Webservice
            {
                struct OfflineRoutingIndoorVersion
                {
                    std::string buildId;
                    std::string submissionComment;
                    std::string createdAt;
                    std::string buildStatus;
                    std::string webManifestUrl;
                    std::string mobileManifestUrl;

                    OfflineRoutingIndoorVersion()
                            : buildId("")
                            , submissionComment("")
                            , createdAt("")
                            , buildStatus("")
                            , webManifestUrl("")
                            , mobileManifestUrl("")
                    {
                    }
                };
            }
        }
    }
}
