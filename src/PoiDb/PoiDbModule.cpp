// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiDbModule.h"
#include "PoiDbWebLoader.h"
#include "PoiDbServiceProvider.h"
#include "SQLiteModule.h"
#include "SQLiteSpellfixOptions.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        PoiDbModule* PoiDbModule::Create(const std::string& poiTableName,
                                         const std::string& srcSqliteDbUrl,
                                         const std::string& destSqliteDbFilename,
                                         Eegeo::Modules::SQLiteModule& sqliteModule)
        {
            PoiDbServiceProvider* pPoiDbServiceProvider = Eegeo_NEW(PoiDbServiceProvider)();
            
            
            std::size_t filenameStart = srcSqliteDbUrl.find_last_of("/\\");
            std::string assetsBaseUrl(srcSqliteDbUrl.substr(0, filenameStart) + '/');
            
            const Eegeo::SQLite::SQLiteSpellfixOptions& spellFixOptions = Eegeo::SQLite::SQLiteSpellfixOptions::Default();
            
            PoiDbWebLoader* pPoiDbWebLoader = Eegeo_NEW(PoiDbWebLoader)(poiTableName,
                                                                        srcSqliteDbUrl,
                                                                        assetsBaseUrl,
                                                                        destSqliteDbFilename,
                                                                        sqliteModule.GetSQLiteDbWebLoader(),
                                                                        sqliteModule.GetSQLiteFtsComponentFactory(),
                                                                        spellFixOptions,
                                                                        *pPoiDbServiceProvider
                                                                        );
            
            
            return Eegeo_NEW(PoiDbModule)(pPoiDbWebLoader, pPoiDbServiceProvider);
        }
        
        PoiDbModule::PoiDbModule(IPoiDbWebLoader* pPoiDbWebLoader,
                                 PoiDbServiceProvider* pServiceProvider)
        : m_pPoiDbWebLoader(pPoiDbWebLoader)
        , m_pServiceProvider(pServiceProvider)
        {
            Eegeo_ASSERT(pPoiDbWebLoader != NULL);
            Eegeo_ASSERT(pServiceProvider != NULL);
        }
        
        PoiDbModule::~PoiDbModule()
        {
            Eegeo_DELETE m_pPoiDbWebLoader;
            Eegeo_DELETE m_pServiceProvider;
        }
        
        bool PoiDbModule::IsPoiDbServiceStarted() const
        {
            return m_pServiceProvider->IsPoiDbServiceStarted();
        }
        
        bool PoiDbModule::TryGetPoiDbService(IPoiDbService*& out_pService) const
        {
            return m_pServiceProvider->TryGetService(out_pService);
        }

    }
}