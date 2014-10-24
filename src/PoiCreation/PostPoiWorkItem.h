// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>

#include "WorkItem.h"
#include "Types.h"
#include "IFileIO.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        class PostPoiWorkItem : public Eegeo::Concurrency::Tasks::WorkItem
        {
        public:
            PostPoiWorkItem(const std::string& title,
                            const std::string& description,
                            Byte* imageData,
                            size_t imageSize,
                            Eegeo::Helpers::IFileIO& fileIO);
            
            void DoWork();
            
            void DoFinalizeOnMainThread();
            
        private:
            std::string m_title;
            std::string m_description;
            Byte* m_imageData;
            size_t m_imageSize;
            Eegeo::Helpers::IFileIO& m_fileIO;
        };
    }
}