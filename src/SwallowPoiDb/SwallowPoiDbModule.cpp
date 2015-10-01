// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SwallowPoiDbModule.h"

#include "SQLiteModule.h"
#include "SQLiteSpellfixOptions.h"

#include "SwallowPoiDbWebLoader.h"
#include "SwallowPoiDbServiceProvider.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        SwallowPoiDbModule* SwallowPoiDbModule::Create(const std::string& srcSqliteDbUrl,
                                                       const std::string& destSqliteDbFilename,
                                                       Eegeo::Modules::SQLiteModule& sqliteModule)
        {
            SwallowPoiDbServiceProvider* pSwallowPoiDbServiceProvider = Eegeo_NEW(SwallowPoiDbServiceProvider)();
            
            std::size_t filenameStart = srcSqliteDbUrl.find_last_of("/\\");
            std::string assetsBaseUrl(srcSqliteDbUrl.substr(0, filenameStart) + '/');
            
            const Eegeo::SQLite::SQLiteSpellfixOptions& spellFixOptions = Eegeo::SQLite::SQLiteSpellfixOptions::Default();
            
            SwallowPoiDbWebLoader* pSwallowPoiDbWebLoader = Eegeo_NEW(SwallowPoiDbWebLoader)(srcSqliteDbUrl,
                                                                                             assetsBaseUrl,
                                                                                             destSqliteDbFilename,
                                                                                             sqliteModule.GetSQLiteDbWebLoader(),
                                                                                             sqliteModule.GetSQLiteFtsComponentFactory(),
                                                                                             spellFixOptions,
                                                                                             *pSwallowPoiDbServiceProvider);
            
            return Eegeo_NEW(SwallowPoiDbModule)(pSwallowPoiDbWebLoader, pSwallowPoiDbServiceProvider);
        }
        
        SwallowPoiDbModule::SwallowPoiDbModule(SwallowPoiDbWebLoader* pSwallowPoiDbWebLoader,
                                               SwallowPoiDbServiceProvider* pServiceProvider)
        : m_pSwallowPoiDbWebLoader(pSwallowPoiDbWebLoader)
        , m_pServiceProvider(pServiceProvider)
        {
            Eegeo_ASSERT(pSwallowPoiDbWebLoader != NULL);
            Eegeo_ASSERT(pServiceProvider != NULL);
        }
        
        SwallowPoiDbModule::~SwallowPoiDbModule()
        {
            Eegeo_DELETE m_pSwallowPoiDbWebLoader;
            Eegeo_DELETE m_pServiceProvider;
        }
        
        SwallowPoiDbWebLoader& SwallowPoiDbModule::GetSwallowPoiDbWebLoader() const
        {
            return *m_pSwallowPoiDbWebLoader;
        }
        
        SwallowPoiDbServiceProvider& SwallowPoiDbModule::GetSwallowPoiDbServiceProvider() const
        {
            return *m_pServiceProvider;
        }
    }
}