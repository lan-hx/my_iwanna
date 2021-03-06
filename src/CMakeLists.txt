cmake_minimum_required(VERSION 3.13)

FILE(GLOB_RECURSE IWANNA_SOURCE
        ${PROJECT_SOURCE_DIR}/src/**/*.cpp
        ${PROJECT_SOURCE_DIR}/src/**/*.ui
        ${PROJECT_SOURCE_DIR}/src/**/*.h
        )
FILE(GLOB_RECURSE IWANNA_SOURCE_MAIN
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.ui
        ${PROJECT_SOURCE_DIR}/src/*.h
        )
message(STATUS "find sources: ${IWANNA_SOURCE} ${IWANNA_SOURCE_MAIN}")
ADD_EXECUTABLE(iwanna ${IWANNA_SOURCE} ${IWANNA_SOURCE_MAIN} ../res/res.qrc)
TARGET_LINK_LIBRARIES(iwanna PRIVATE Qt5::Widgets Qt5::Multimedia)
set_target_properties(iwanna PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER huaji
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )
add_dependencies(iwanna clang_format)

add_custom_command(TARGET iwanna POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res/music
        $<TARGET_FILE_DIR:iwanna>/music)

if(WIN32)
    set(QT_DEPLOY_EXE "${QT_PREFIX_DIR}/bin/windeployqt.exe")
    message("QT_DEPLOY_EXE: ${QT_DEPLOY_EXE}")
    add_custom_command(TARGET iwanna POST_BUILD
            COMMAND ${QT_DEPLOY_EXE} $<TARGET_FILE:iwanna>)
endif()
