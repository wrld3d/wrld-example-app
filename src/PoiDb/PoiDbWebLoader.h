// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiDb.h"
#include "IPoiDbWebLoader.h"
#include "Types.h"
#include "SQLite.h"
#include "SQLiteDbWebLoaderCompletedHandler.h"
#include "SQLiteSpellfixOptions.h"

#include <string>

namespace ExampleApp
{
    namespace PoiDb
    {
        class PoiDbWebLoader : public IPoiDbWebLoader, Eegeo::NonCopyable
        {
        public:
            PoiDbWebLoader(const std::string& poiTableName,
                           const std::string& srcSqliteDbUrl,
                           const std::string& assetsBaseUrl,
                           const std::string& destSqliteDbFilename,
                           Eegeo::SQLite::SQLiteDbWebLoader& sqliteWebLoader,
                           Eegeo::SQLite::SQLiteFtsComponentFactory& ftsComponentFactory,
                           const Eegeo::SQLite::SQLiteSpellfixOptions& spellFixOptions,
                           Eegeo::Helpers::ICallback1<IPoiDbService*>& serviceStartedCallback);
            
            virtual ~PoiDbWebLoader();
            
            virtual void Load();
            
            virtual void WebLoadComplete(const Eegeo::SQLite::SQLiteDbWebLoaderResponse& webLoaderResponse);
            
        private:
            const std::string m_poiTableName;
            const std::string m_srcSqliteDbUrl;
            const std::string m_assetsBaseUrl;
            const std::string m_destSqliteDbFilename;

            Eegeo::SQLite::SQLiteDbWebLoader& m_sqliteWebLoader;
            Eegeo::SQLite::SQLiteFtsComponentFactory& m_ftsComponentFactory;
            const Eegeo::SQLite::SQLiteSpellfixOptions m_spellFixOptions;
            Eegeo::Helpers::ICallback1<IPoiDbService*>& m_serviceStartedCallback;
            Eegeo::SQLite::TSQLiteDbWebLoaderCompletedHandler<PoiDbWebLoader> m_webLoadCompleteHandler;
        };
    }
}
