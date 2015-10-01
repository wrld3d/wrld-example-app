// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "ISwallowPoiDbModule.h"

#include <string>

#include "Modules.h"
#include "Types.h"

#include "SwallowPoiDb.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        class SwallowPoiDbServiceProvider;
        
        class SwallowPoiDbModule : public ISwallowPoiDbModule, Eegeo::NonCopyable
        {
        public:
            static SwallowPoiDbModule* Create(const std::string& srcSqliteDbUrl,
                                              const std::string& destSqliteDbFilename,
                                              Eegeo::Modules::SQLiteModule& sqliteModule);
            
            ~SwallowPoiDbModule();
            
            SwallowPoiDbWebLoader& GetSwallowPoiDbWebLoader() const;
            
            SwallowPoiDbServiceProvider& GetSwallowPoiDbServiceProvider() const;
            
        private:
            SwallowPoiDbModule(SwallowPoiDbWebLoader* pSwallowPoiDbWebLoader,
                               SwallowPoiDbServiceProvider* pServiceProvider);
            
            SwallowPoiDbWebLoader* m_pSwallowPoiDbWebLoader;
            SwallowPoiDbServiceProvider* m_pServiceProvider;
        };
    }
}