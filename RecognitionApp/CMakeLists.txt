cmake_minimum_required(VERSION 3.5)

project(RecognitionApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)

set(PROJECT_SOURCES
        Resources/Resource.qrc
        include/Image/Image.h
        include/Image/ImageProperties.h
        include/Image/ImageExtention.h
        include/Recognition/IRecognizable.h
        include/Recognition/Method/Contour.h
        include/Recognition/Method/Color.h
        include/Tool/Convert/Convert.h
        include/mainwindow.h
        include/filterdialog.h
        Image/Image.cpp
        Image/ImageProperties.cpp
        Recognition/Method/Contour.cpp
        Recognition/Method/Color.cpp
        Tool/Convert/Convert.cpp
        form/mainwindow.ui
        form/filterdialog.ui
        mainwindow.cpp
        filterdialog.cpp
        main.cpp
)
set(CMAKE_AUTOUIC_SEARCH_PATHS
        form)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RecognitionApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET RecognitionApp APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(RecognitionApp SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(RecognitionApp
            ${PROJECT_SOURCES}
        )
    endif()
endif()

include_directories(include)
include_directories(include/Image)
include_directories(include/Recognition)
include_directories(include/Recognition/Method)
include_directories(include/Tool/Convert)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(RecognitionApp
PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${OpenCV_LIBS}
)

set_target_properties(RecognitionApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RecognitionApp)
endif()
