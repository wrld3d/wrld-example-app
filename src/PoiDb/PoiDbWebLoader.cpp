// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiDbWebLoader.h"
#include "PoiDbService.h"
#include "SQLiteDbWebLoader.h"
#include "SQLiteDbConnection.h"
#include "SQLiteFtsSnippetFormattingConfig.h"
#include "SQLiteFtsComponent.h"
#include "SQLiteFtsComponentFactory.h"
#include "SQLiteLatLongQueryBuilder.h"

#include "IteratorHelpers.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        PoiDbWebLoader::PoiDbWebLoader(const std::string& poiTableName,
                                       const std::string& srcSqliteDbUrl,
                                       const std::string& assetsBaseUrl,
                                       const std::string& destSqliteDbFilename,
                                       Eegeo::SQLite::SQLiteDbWebLoader& sqliteWebLoader,
                                       Eegeo::SQLite::SQLiteFtsComponentFactory& ftsComponentFactory,
                                       const Eegeo::SQLite::SQLiteSpellfixOptions& spellFixOptions,
                                       Eegeo::Helpers::ICallback1<IPoiDbService*>& serviceStartedCallback)
        : m_poiTableName(poiTableName)
        , m_srcSqliteDbUrl(srcSqliteDbUrl)
        , m_assetsBaseUrl(assetsBaseUrl)
        , m_destSqliteDbFilename(destSqliteDbFilename)
        , m_sqliteWebLoader(sqliteWebLoader)
        , m_ftsComponentFactory(ftsComponentFactory)
        , m_spellFixOptions(spellFixOptions)
        , m_serviceStartedCallback(serviceStartedCallback)
        , m_webLoadCompleteHandler(this, &PoiDbWebLoader::WebLoadComplete)
        {
            
        }
        
        PoiDbWebLoader::~PoiDbWebLoader()
        {
        }
        
        void PoiDbWebLoader::Load()
        {
            m_sqliteWebLoader.Load(m_srcSqliteDbUrl, m_destSqliteDbFilename, m_webLoadCompleteHandler);
        }
        
        void PoiDbWebLoader::WebLoadComplete(const Eegeo::SQLite::SQLiteDbWebLoaderResponse& webLoaderResponse)
        {
            IPoiDbService* pPoiDbService = NULL;
            
            if (!webLoaderResponse.succeeded)
            {
                Eegeo_TTY("Failed to download poi db");
                m_serviceStartedCallback(pPoiDbService);
                return;
            }
            

            Eegeo::SQLite::SQLiteDbConnection* pSQLiteDbConnection = Eegeo_NEW(Eegeo::SQLite::SQLiteDbConnection)();
            
            bool dbOpened = pSQLiteDbConnection->Open(webLoaderResponse.fullyQualifiedDbPathname);
            if (!dbOpened)
            {
                Eegeo_ASSERT(false, "Unable to open poi db connection");
                return;
            }
            

            
            const std::string ftsColumnNames[] = { "name", "job_title", "working_group", "office_location", "desk_code" };
            const float ftsColumnRankWeights[] = { 1.f, 0.5f, 0.5f, 0.5f, 0.1f };
            
            
            Eegeo::SQLite::SQLiteFtsSnippetFormattingConfig snippetConfig = Eegeo::SQLite::SQLiteFtsSnippetFormattingConfig::Default();
            
            Eegeo::SQLite::SQLiteFtsComponent* pPoiFtsComponent = m_ftsComponentFactory.Create(
                                                              *pSQLiteDbConnection,
                                                              m_poiTableName,
                                                              Eegeo::Helpers::makeVector(ftsColumnNames),
                                                              Eegeo::Helpers::makeVector(ftsColumnRankWeights),
                                                              snippetConfig,
                                                              Eegeo::SQLite::SQLiteFtsTokenizerType_PorterStemming
                                                              );
            
            Eegeo::SQLite::SQLiteLatLongQueryBuilder* pLatLongQueryBuilder = Eegeo_NEW(Eegeo::SQLite::SQLiteLatLongQueryBuilder)("latitude_degrees", "longitude_degrees");
            
            pPoiDbService = Eegeo_NEW(PoiDbService)(pSQLiteDbConnection, pPoiFtsComponent, pLatLongQueryBuilder, m_assetsBaseUrl, m_spellFixOptions);
                                        
            m_serviceStartedCallback(pPoiDbService);
        }
    }
}