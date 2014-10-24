// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PostPoiWorkItem.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        PostPoiWorkItem::PostPoiWorkItem(const std::string& title,
                                         const std::string& description,
                                         Byte* imageData,
                                         size_t imageSize,
                                         Eegeo::Helpers::IFileIO& fileIO)
        : m_title(title)
        , m_description(description)
        , m_imageData(NULL)
        , m_imageSize(imageSize)
        , m_fileIO(fileIO)
        {
            m_imageData = Eegeo_NEW(Byte)(*imageData);
        }
        
        void PostPoiWorkItem::DoWork()
        {
            Eegeo_TTY("Details: %s, %s, %d\n", m_title.c_str(), m_description.c_str(), m_imageSize);
            std::string path = "proper_bytes_test_deep_copy.jpg";
            
            if (!m_fileIO.WriteFile(m_imageData, m_imageSize, path))
            {
                Eegeo_TTY("Couldn't write file: %s\n", path.c_str());
            }
        }
        
        void PostPoiWorkItem::DoFinalizeOnMainThread()
        {
            Eegeo_TTY("Finished caching file!\n");
            Eegeo_DELETE m_imageData;
        }
    }
}