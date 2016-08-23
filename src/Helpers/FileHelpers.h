// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Helpers.h"
#include <string>

namespace ExampleApp
{
    namespace Helpers
    {
        namespace FileHelpers
        {
            std::string GetFileContentsAsString(Eegeo::Helpers::IFileIO& fileIO, const std::string& fileName);
        }
    }
}
