set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
set(PROJECT_SOURCES
        main.cpp
        word.h word.cpp
        wordProcess.h wordProcess.cpp
        fileIO.h fileIO.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(my_vocabulary
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
endif()
target_link_libraries(my_vocabulary PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


set_target_properties(my_vocabulary PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(my_vocabulary)
endif()

#用于提高警告等级
if(MSVC)
  target_compile_options(my_vocabulary PRIVATE /W4 )
else()
  target_compile_options(my_vocabulary PRIVATE -Wall -Wextra )
  #-Wpedantic -Werror)
endif()
