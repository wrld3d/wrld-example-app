// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"

#include "SwallowPoiDb.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        class SwallowPoiDbServiceProvider : public Eegeo::Helpers::TCallback1<SwallowPoiDbServiceProvider, SwallowPoiDbCombinedService*>, Eegeo::NonCopyable
        {
        public:
            SwallowPoiDbServiceProvider();
            
            ~SwallowPoiDbServiceProvider();
            
            bool TryGetSwallowPoiDbService(SwallowPoiDbCombinedService*& out_pService) const;
            
            void SwallowPoiDbWebLoaderCompleted(SwallowPoiDbCombinedService*& pSwallowPoiDbService);
        private:
            SwallowPoiDbCombinedService* m_pSwallowPoiDbService;
        };
    }
}