# qt compile environment
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
#find_package(Qt6 REQUIRED COMPONENTS  Core Gui  WebEngineWidgets)
find_package(Qt6 REQUIRED COMPONENTS Core Gui WebEngineWidgets Sql)
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
)


qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)
target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Core
    Qt::Gui
    Qt::WebEngineWidgets
    Qt6::Sql
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
