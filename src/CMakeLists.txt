cmake_minimum_required(VERSION 3.13)

FILE(GLOB_RECURSE IWANNA_SOURCE
        ${PROJECT_SOURCE_DIR}/src/*/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*/*/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*/*.ui
        ${PROJECT_SOURCE_DIR}/src/*/*/*.ui
#        ${PROJECT_SOURCE_DIR}/src/*/*.c
#        ${PROJECT_SOURCE_DIR}/src/*/*/*.c
        )
if (DEFINED IWANNA_DYNAMIC_BUILD)
    add_library(iwanna_lib SHARED ${IWANNA_SOURCE})
else ()
    ADD_LIBRARY(iwanna_lib STATIC ${IWANNA_SOURCE})
endif ()
TARGET_LINK_LIBRARIES(iwanna_lib PRIVATE Qt5::Widgets)

ADD_EXECUTABLE(iwanna main.cpp mainwindow.cpp mainwindow.ui)
TARGET_LINK_LIBRARIES(iwanna PRIVATE Qt5::Widgets iwanna_lib)
set_target_properties(iwanna PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER huaji
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )
add_dependencies(iwanna clang_format)

if(WIN32)
    set(QT_DEPLOY_EXE "${QT_PREFIX_DIR}/bin/windeployqt.exe")
    message("QT_DEPLOY_EXE: ${QT_DEPLOY_EXE}")
    add_custom_command(TARGET iwanna POST_BUILD
            COMMAND ${QT_DEPLOY_EXE} $<TARGET_FILE:iwanna>)
endif()
