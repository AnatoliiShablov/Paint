cmake_minimum_required(VERSION 3.14)

project(Paint LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(ANDROID)
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    if (ANDROID_ABI STREQUAL "armeabi-v7a")
        set(ANDROID_EXTRA_LIBS
            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
    endif()
endif()

find_package(Qt6 COMPONENTS Core Quick LinguistTools REQUIRED)

set(TS_FILES Paint_ru_RU.ts)

if(ANDROID)
    add_library(Paint SHARED
      main.cpp
      PaintModel.hpp
      PaintModel.cpp
      ColorChooserModel.hpp
      ColorChooserModel.cpp
      qml.qrc
      ${TS_FILES}
    )
else()
    add_executable(Paint
      main.cpp
      PaintModel.hpp
      PaintModel.cpp
      ColorChooserModel.hpp
      ColorChooserModel.cpp
      qml.qrc
      ${TS_FILES}
    )
endif()

target_compile_definitions(Paint
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Paint
  PRIVATE Qt6::Core Qt6::Quick)

qt_add_translation(qmFiles ${TS_FILES})
