// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include <vector>

#include "Types.h"
#include "SQLite.h"
#include "SQLiteDbWebLoaderCompletedHandler.h"
#include "SQLiteSpellfixOptions.h"

#include "SwallowPoiDb.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        class SwallowPoiDbWebLoader : private Eegeo::NonCopyable
        {
        public:
            SwallowPoiDbWebLoader(const std::string& srcSqliteDbUrl,
                                  const std::string& assetsBaseUrl,
                                  const std::string& destSqliteDbFilename,
                                  Eegeo::SQLite::SQLiteDbWebLoader& sqliteWebLoader,
                                  Eegeo::SQLite::SQLiteFtsComponentFactory& ftsComponentFactory,
                                  const Eegeo::SQLite::SQLiteSpellfixOptions& spellFixOptions,
                                  Eegeo::Helpers::ICallback1<SwallowPoiDbCombinedService*>& serviceStartedCallback);
            
            virtual ~SwallowPoiDbWebLoader();
            
            virtual void Load();
            
            virtual void WebLoadComplete(const Eegeo::SQLite::SQLiteDbWebLoaderResponse& webLoaderResponse);
            
        private:
            
            Eegeo::SQLite::SQLiteFtsComponent* BuildFtsComponent(Eegeo::SQLite::SQLiteDbConnection& pSQLiteDbConnection,
                                                                 const std::string& tableName,
                                                                 const std::vector<std::string>& ftsColumnNames,
                                                                 const std::vector<float>& ftsColumnWeights) const;
            
            const std::string m_srcSqliteDbUrl;
            const std::string m_assetsBaseUrl;
            const std::string m_destSqliteDbFilename;
            
            Eegeo::SQLite::SQLiteDbWebLoader& m_sqliteWebLoader;
            Eegeo::SQLite::SQLiteFtsComponentFactory& m_ftsComponentFactory;
            const Eegeo::SQLite::SQLiteSpellfixOptions m_spellFixOptions;
            Eegeo::Helpers::ICallback1<SwallowPoiDbCombinedService*>& m_serviceStartedCallback;
            Eegeo::SQLite::TSQLiteDbWebLoaderCompletedHandler<SwallowPoiDbWebLoader> m_webLoadCompleteHandler;
        };
    }
}
