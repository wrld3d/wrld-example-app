//
//  FileIOExample.cpp
//  ExampleApp
//
//  Created by eeGeo on 30/04/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#include "FileIOExample.h"
#include <sstream>
#include <vector>

using namespace Eegeo::Helpers;

namespace Examples
{
    FileIOExample::FileIOExample(IFileIO& fileIO)
    :fileIO(fileIO)
    {
    }
    
    void FileIOExample::Start()
    {
        srand(time(0));
        Byte data[] = { 1, 2, 3, 4, 5 };
        
        std::stringstream ss;
        ss << "mydata_" << rand() << ".bytes";
        std::string filename = ss.str();
        
        bool exists = fileIO.Exists(filename);
        
        Eegeo_TTY("%s %s\n", filename.c_str(), exists ? "exists" : "does not exist");
        if(!fileIO.WriteFile(data, 5ul, filename))
        {
            Eegeo_TTY("Failed to write to filesystem!\n");
            return;
        }
        
        exists = fileIO.Exists(filename);
        Eegeo_TTY("mydata.bytes now %s\n", exists ? "exists" : "does not exist");
        
        std::fstream stream;
        size_t size;
        if(fileIO.OpenFile(stream, size, filename))
        {
            Eegeo_TTY("Opened File!\n");
            
            std::vector<Byte> readBackData;
            readBackData.resize(size);
            stream.read((char*)&readBackData[0], size);
            
            for(int i = 0; i < size; ++ i)  {
                Eegeo_TTY("Read %d at position %d\n", readBackData[i], i);
            }
        }
        
        stream.close();
        
        Eegeo_TTY("Done!\n");
    }
}
