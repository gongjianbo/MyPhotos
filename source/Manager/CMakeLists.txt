project(myphotos_manager)

set(MANAGER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR})

set(MANAGER_SOURCES
    ManagerRegister.h
    FileManager.h
    FileManager.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Concurrent)

add_library(myphotos_manager ${MANAGER_SOURCES})

target_link_libraries(myphotos_manager PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::Concurrent
)

target_include_directories(myphotos_manager PUBLIC
    ${MANAGER_INCLUDE_DIR}
)
