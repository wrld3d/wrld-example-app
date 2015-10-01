// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "SwallowPoiDb.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        class ISwallowPoiDbModule
        {
        public:
            virtual ~ISwallowPoiDbModule() {;}
            
            virtual SwallowPoiDbWebLoader& GetSwallowPoiDbWebLoader() const = 0;
            
            virtual SwallowPoiDbServiceProvider& GetSwallowPoiDbServiceProvider() const = 0;
        };
    }
}