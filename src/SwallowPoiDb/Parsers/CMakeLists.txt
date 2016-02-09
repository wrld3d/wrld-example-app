set(headers ${headers} ../src/SwallowPoiDb/Parsers
)
set(currsources
  ../src/SwallowPoiDb/Parsers/ISwallowPoiDbParser.h
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbDepartmentParser.cpp
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbDepartmentParser.h
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbEmployeeParser.cpp
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbEmployeeParser.h
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbFacilityParser.cpp
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbFacilityParser.h
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbMeetingRoomParser.cpp
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbMeetingRoomParser.h
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbOfficeParser.cpp
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbOfficeParser.h
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbParseHelper.cpp
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbParseHelper.h
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbTransitionParser.cpp
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbTransitionParser.h
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbWorkingGroupParser.cpp
  ../src/SwallowPoiDb/Parsers/SwallowPoiDbWorkingGroupParser.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SwallowPoiDb\\Parsers FILES ${currsources})
