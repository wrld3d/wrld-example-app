//
//  FileIOExample.h
//  ExampleApp
//
//  Created by eeGeo on 30/04/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__FileIOExample__
#define __ExampleApp__FileIOExample__

#include "IExample.h"

#include "IFileIO.h"

namespace Examples
{
    class FileIOExample : public IExample
    {
    private:
        Eegeo::Helpers::IFileIO& fileIO;
        
    public:
        FileIOExample(Eegeo::Helpers::IFileIO& fileIO);
        
        void Start();
        void Update() {}
        void Draw() {}
        void Suspend() {}
    };
}


#endif /* defined(__ExampleApp__FileIOExample__) */
