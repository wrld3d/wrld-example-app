// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SwallowPoiDbWebLoader.h"

#include <map>
#include <vector>

#include "SQLiteDbWebLoader.h"
#include "SQLiteDbConnection.h"
#include "SQLiteFtsSnippetFormattingConfig.h"
#include "SQLiteFtsComponent.h"
#include "SQLiteFtsComponentFactory.h"
#include "SQLiteTable.h"

#include "IteratorHelpers.h"
#include "SwallowPoiDbConstants.h"
#include "SwallowPoiDbCombinedService.h"
#include "SwallowPoiDbEmployeeParser.h"
#include "SwallowPoiDbDepartmentParser.h"
#include "SwallowPoiDbFacilityParser.h"
#include "SwallowPoiDbMeetingRoomParser.h"
#include "SwallowPoiDbOfficeParser.h"
#include "SwallowPoiDbService.h"
#include "SwallowPoiDbTransitionParser.h"
#include "SwallowPoiDbWorkingGroupParser.h"
#include "SwallowSearchConstants.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        SwallowPoiDbWebLoader::SwallowPoiDbWebLoader(const std::string& srcSqliteDbUrl,
                                                     const std::string& assetsBaseUrl,
                                                     const std::string& destSqliteDbFilename,
                                                     Eegeo::SQLite::SQLiteDbWebLoader& sqliteWebLoader,
                                                     Eegeo::SQLite::SQLiteFtsComponentFactory& ftsComponentFactory,
                                                     const Eegeo::SQLite::SQLiteSpellfixOptions& spellFixOptions,
                                                     Eegeo::Helpers::ICallback1<SwallowPoiDbCombinedService*>& serviceStartedCallback)
        : m_srcSqliteDbUrl(srcSqliteDbUrl)
        , m_assetsBaseUrl(assetsBaseUrl)
        , m_destSqliteDbFilename(destSqliteDbFilename)
        , m_sqliteWebLoader(sqliteWebLoader)
        , m_ftsComponentFactory(ftsComponentFactory)
        , m_spellFixOptions(spellFixOptions)
        , m_serviceStartedCallback(serviceStartedCallback)
        , m_webLoadCompleteHandler(this, &SwallowPoiDbWebLoader::WebLoadComplete)
        {
            
        }
        
        SwallowPoiDbWebLoader::~SwallowPoiDbWebLoader()
        {
        }
        
        void SwallowPoiDbWebLoader::Load()
        {
            m_sqliteWebLoader.Load(m_srcSqliteDbUrl, m_destSqliteDbFilename, m_webLoadCompleteHandler);
        }
        
        void SwallowPoiDbWebLoader::WebLoadComplete(const Eegeo::SQLite::SQLiteDbWebLoaderResponse& webLoaderResponse)
        {
            SwallowPoiDbCombinedService* pSwallowPoiDbService = NULL;
            
            if (!webLoaderResponse.succeeded)
            {
                Eegeo_TTY("Failed to download poi db");
                m_serviceStartedCallback(pSwallowPoiDbService);
                return;
            }
            
            Eegeo::SQLite::SQLiteDbConnection* pSQLiteDbConnection = Eegeo_NEW(Eegeo::SQLite::SQLiteDbConnection)();
            
            bool dbOpened = pSQLiteDbConnection->Open(webLoaderResponse.fullyQualifiedDbPathname);
            if (!dbOpened)
            {
                Eegeo_ASSERT(false, "Unable to open poi db connection");
                return;
            }
            
            std::map<std::string, SwallowPoiDbService*> serviceMap;
            
            serviceMap[Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME] = Eegeo_NEW(SwallowPoiDbService)(BuildFtsComponent(*pSQLiteDbConnection,
                                                                                                                                  Constants::EmployeeTableName,
                                                                                                                                  Eegeo::Helpers::makeVector(Constants::EmployeeFtsColumnNames),
                                                                                                                                  Eegeo::Helpers::makeVector(Constants::EmployeeFtsColumnWeights)),
                                                                                                                m_spellFixOptions,
                                                                                                                Eegeo_NEW(Parsers::SwallowPoiDbEmployeeParser),
                                                                                                                m_assetsBaseUrl);
            
            serviceMap[Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME] = Eegeo_NEW(SwallowPoiDbService)(BuildFtsComponent(*pSQLiteDbConnection,
                                                                                                                                        Constants::MeetingRoomTableName,
                                                                                                                                        Eegeo::Helpers::makeVector(Constants::MeetingRoomFtsColumnNames),
                                                                                                                                        Eegeo::Helpers::makeVector(Constants::MeetingRoomFtsColumnWeights)),
                                                                                                                      m_spellFixOptions,
                                                                                                                      Eegeo_NEW(Parsers::SwallowPoiDbMeetingRoomParser),
                                                                                                                      m_assetsBaseUrl);
            
            serviceMap[Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME] = Eegeo_NEW(SwallowPoiDbService)(BuildFtsComponent(*pSQLiteDbConnection,
                                                                                                                                         Constants::WorkingGroupTableName,
                                                                                                                                         Eegeo::Helpers::makeVector(Constants::WorkingGroupFtsColumnNames),
                                                                                                                                         Eegeo::Helpers::makeVector(Constants::WorkingGroupFtsColumnWeights)),
                                                                                                                       m_spellFixOptions,
                                                                                                                       Eegeo_NEW(Parsers::SwallowPoiDbWorkingGroupParser),
                                                                                                                       m_assetsBaseUrl);
            
            serviceMap[Search::Swallow::SearchConstants::FACILITY_CATEGORY_NAME] = Eegeo_NEW(SwallowPoiDbService)(BuildFtsComponent(*pSQLiteDbConnection,
                                                                                                                                    Constants::FacilityTableName,
                                                                                                                                    Eegeo::Helpers::makeVector(Constants::FacilityFtsColumnNames),
                                                                                                                                    Eegeo::Helpers::makeVector(Constants::FacilityFtsColumnWeights)),
                                                                                                                  m_spellFixOptions,
                                                                                                                  Eegeo_NEW(Parsers::SwallowPoiDbFacilityParser),
                                                                                                                  m_assetsBaseUrl);
            
            serviceMap[Search::Swallow::SearchConstants::OFFICE_CATEGORY_NAME] = Eegeo_NEW(SwallowPoiDbService)(BuildFtsComponent(*pSQLiteDbConnection,
                                                                                                                                  Constants::OfficeTableName,
                                                                                                                                  Eegeo::Helpers::makeVector(Constants::OfficeFtsColumnNames),
                                                                                                                                  Eegeo::Helpers::makeVector(Constants::OfficeFtsColumnWeights)),
                                                                                                                m_spellFixOptions,
                                                                                                                Eegeo_NEW(Parsers::SwallowPoiDbOfficeParser),
                                                                                                                m_assetsBaseUrl);
            
            serviceMap[Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME] = Eegeo_NEW(SwallowPoiDbService)(BuildFtsComponent(*pSQLiteDbConnection,
                                                                                                                                  Constants::DepartmentTableName,
                                                                                                                                  Eegeo::Helpers::makeVector(Constants::DepartmentFtsColumnNames),
                                                                                                                                  Eegeo::Helpers::makeVector(Constants::DepartmentFtsColumnWeights)),
                                                                                                                m_spellFixOptions,
                                                                                                                Eegeo_NEW(Parsers::SwallowPoiDbDepartmentParser),
                                                                                                                m_assetsBaseUrl);
            
            Eegeo::SQLite::SQLiteTable* transitionsTable = Eegeo_NEW(Eegeo::SQLite::SQLiteTable)(Constants::TransitionTableName, *pSQLiteDbConnection);
            
            pSwallowPoiDbService = Eegeo_NEW(SwallowPoiDbCombinedService)(serviceMap,
                                                                          transitionsTable);
            
            m_serviceStartedCallback(pSwallowPoiDbService);
        }
        
        Eegeo::SQLite::SQLiteFtsComponent* SwallowPoiDbWebLoader::BuildFtsComponent(Eegeo::SQLite::SQLiteDbConnection& pSQLiteDbConnection,
                                                                                    const std::string& tableName,
                                                                                    const std::vector<std::string>& ftsColumnNames,
                                                                                    const std::vector<float>& ftsColumnRankWeights) const
        {
            Eegeo::SQLite::SQLiteFtsSnippetFormattingConfig snippetConfig = Eegeo::SQLite::SQLiteFtsSnippetFormattingConfig::Default();
            
            return m_ftsComponentFactory.Create(pSQLiteDbConnection,
                                                tableName,
                                                ftsColumnNames,
                                                ftsColumnRankWeights,
                                                snippetConfig,
                                                Eegeo::SQLite::SQLiteFtsTokenizerType_PorterStemming);
        }
    }
}