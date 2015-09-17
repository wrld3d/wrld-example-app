// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiDb.h"
#include "SQLite.h"

#include <string>

namespace ExampleApp
{
    namespace PoiDb
    {
        class IPoiDbWebLoader
        {
        public:
            virtual ~IPoiDbWebLoader() {;}
            
            virtual void Load() = 0;
        };
    }
}
