project(myphotos_core)

set(CORE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR})

set(CORE_SOURCES
    CoreRegister.h
    MPCoreDef.h
    MPCore.h
    MPCore.cpp
    MPConfig.h
    MPConfig.cpp
    MPApplication.h
    MPApplication.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick)

add_library(myphotos_core ${CORE_SOURCES})

target_link_libraries(myphotos_core PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
)

target_include_directories(myphotos_core PUBLIC
    ${CORE_INCLUDE_DIR}
)
