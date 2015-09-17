// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IPoiDbModule.h"
#include "Types.h"
#include "PoiDb.h"
#include "Modules.h"
#include "PoiDbWebLoader.h"

#include <string>

namespace ExampleApp
{
    namespace PoiDb
    {
        class PoiDbServiceProvider;
        
        class PoiDbModule : public IPoiDbModule, Eegeo::NonCopyable
        {
        public:
            static PoiDbModule* Create(const std::string& poiTableName,
                                       const std::string& srcSqliteDbUrl,
                                       const std::string& destSqliteDbFilename,
                                       Eegeo::Modules::SQLiteModule& sqliteModule);
        
            PoiDbModule(IPoiDbWebLoader* pPoiDbWebLoader,
                        PoiDbServiceProvider* pServiceProvider);
            
            ~PoiDbModule();
        
            IPoiDbWebLoader& GetPoiDbWebLoader() const { return *m_pPoiDbWebLoader; }
            
            bool IsPoiDbServiceStarted() const;
            
            bool TryGetPoiDbService(IPoiDbService*& out_pService) const;
        
        private:
            IPoiDbWebLoader* m_pPoiDbWebLoader;
            PoiDbServiceProvider* m_pServiceProvider;
        };
    }
}