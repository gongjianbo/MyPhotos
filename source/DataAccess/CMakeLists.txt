project(myphotos_dataaccess)

set(DATAACCESS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR})

set(DATAACCESS_SOURCES
    DataAccessDef.h
    DataAccessDef.cpp
    DataAccessRegister.h
    FileInfoAccess.h
    FileInfoAccess.cpp
    FileInfoConnection.h
    FileInfoConnection.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Concurrent Sql)

add_library(myphotos_dataaccess ${DATAACCESS_SOURCES})

target_link_libraries(myphotos_dataaccess PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::Concurrent
    Qt6::Sql
    myphotos_core
)

target_include_directories(myphotos_dataaccess PUBLIC
    ${DATAACCESS_INCLUDE_DIR}
)
