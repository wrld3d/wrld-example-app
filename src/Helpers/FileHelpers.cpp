// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "FileHelpers.h"

#include <fstream>
#include "Types.h"
#include "IFileIO.h"


namespace ExampleApp
{
    namespace Helpers
    {
        namespace FileHelpers
        {
        	std::string GetFileContentsAsString(Eegeo::Helpers::IFileIO& fileIO, const std::string& fileName)
            {
                std::fstream file;
                std::size_t size;

                const bool openedSuccessfully = fileIO.OpenFile(file, size, fileName, std::ios::in);
                Eegeo_ASSERT(openedSuccessfully, "Failed to open file: %s", fileName.c_str());

                const std::string text(
                        (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

                file.close();
                return text;
            }
        }
    }
}
