# qt compile environment
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
#find_package(Qt6 REQUIRED COMPONENTS  Core Gui  WebEngineWidgets)
find_package(Qt6 REQUIRED COMPONENTS Core Gui WebEngineWidgets Sql Xml)
#find_package(Qt6 REQUIRED COMPONENTS WebEngineWidgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.h mainwindow.cpp
        webview.h webview.cpp
        word.h word.cpp
        myschemehandler.h myschemehandler.cpp
        databasemanager.h databasemanager.cpp
        wordprocess.h wordprocess.cpp
        articlemaker.h articlemaker.cpp
        articlepad.h articlepad.cpp
        vocabularytest.h vocabularytest.cpp
        learningmodel.h learningmodel.cpp
        translatearea.h translatearea.cpp
        resource.qrc
)

# 从 goldendict copy 过来的生成版本信息的方法
block() # generate version.txt
    string(TIMESTAMP build_time)
    find_package(Git)
    if (EXISTS "${CMAKE_SOURCE_DIR}/.git" AND GIT_FOUND)
        execute_process(
                COMMAND ${GIT_EXECUTABLE} -C "${CMAKE_SOURCE_DIR}" rev-parse --short HEAD
                OUTPUT_STRIP_TRAILING_WHITESPACE
                OUTPUT_VARIABLE GIT_HASH)
        file(WRITE "${CMAKE_SOURCE_DIR}/src/rsc/version.txt"
            "VERSION: ${PROJECT_VERSION}.${GIT_HASH}\n"
            "TIME: ${build_time}\n"
            "COMPLIER: ${CMAKE_CXX_COMPILER_ID}\n"
            "COMPLIER VERSION: ${CMAKE_CXX_COMPILER_VERSION}\n"
            "BUILD TYPE: ${CMAKE_BUILD_TYPE}\n"
        )
    else () # not built in a git repo
        file(WRITE "${CMAKE_SOURCE_DIR}/src/rsc/version.txt" "${PROJECT_VERSION} at ${build_time}")
    endif ()
endblock()


qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)
target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Core
    Qt::Gui
    Qt::WebEngineWidgets
    Qt6::Sql
    Qt6::Xml
)


set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

#用于提高警告等级
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 )
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra )
  #-Wpedantic -Werror)
endif()


