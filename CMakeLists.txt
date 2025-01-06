cmake_minimum_required(VERSION 3.16)
project(hitster VERSION 0.8.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Core Gui Quick QuickControls2 LinguistTools Multimedia WebView)

qt_standard_project_setup(
	REQUIRES 6.7
	I18N_TRANSLATED_LANGUAGES sv
)

qt_add_executable(${PROJECT_NAME})

add_subdirectory(src)
include(QmlModule.cmake)

qt_add_translations(${PROJECT_NAME}
	TS_FILE_DIR ts
)

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
	# QML requires headers in root
	"${CMAKE_CURRENT_SOURCE_DIR}/src/qml"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/entity"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE APP_NAME="${PROJECT_NAME}")
target_compile_definitions(${PROJECT_NAME} PRIVATE APP_VERSION="v${PROJECT_VERSION}")
target_compile_definitions(${PROJECT_NAME} PRIVATE ORG_NAME="${PROJECT_NAME}")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(${PROJECT_NAME} PRIVATE QT_QML_DEBUG)
endif ()

if (ANDROID)
	include(cmake/AndroidOpenSSL.cmake)
	add_android_openssl_libraries(${PROJECT_NAME})
endif ()

set(SPOTIFY_CLIENT_ID "" CACHE STRING "Spotify client ID")
set(SPOTIFY_CLIENT_SECRET "" CACHE STRING "Spotify client secret")

target_compile_definitions(${PROJECT_NAME} PRIVATE SPOTIFY_CLIENT_ID="${SPOTIFY_CLIENT_ID}")
target_compile_definitions(${PROJECT_NAME} PRIVATE SPOTIFY_CLIENT_SECRET="${SPOTIFY_CLIENT_SECRET}")

include(cmake/AndroidVersionCode.cmake)
android_version_code(ANDROID_VERSION_CODE)

include(deps/zxing.cmake)
target_link_libraries(${PROJECT_NAME} PRIVATE ZXing)

set_target_properties(${PROJECT_NAME} PROPERTIES
	WIN32_EXECUTABLE TRUE
	MACOSX_BUNDLE TRUE
	MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/res/app/Info.plist"
	QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res/app/android"
	QT_ANDROID_VERSION_NAME ${PROJECT_VERSION}
	QT_ANDROID_VERSION_CODE ${ANDROID_VERSION_CODE}
	QT_ANDROID_PACKAGE_NAME "com.kraxarn.${PROJECT_NAME}"
	QT_ANDROID_APP_NAME "Hitster"
	QT_ANDROID_APP_ICON "@mipmap/ic_launcher"
	QT_ENABLE_VERBOSE_DEPLOYMENT TRUE
)

if (ANDROID)
	# Deprecated, but ffmpeg backend adds ~15 mb and not really used
	set_target_properties(${PROJECT_NAME} PROPERTIES
		QT_DEFAULT_MEDIA_BACKEND "android"
	)
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE
	Qt6::Core
	Qt6::Gui
	Qt6::Quick
	Qt6::QuickControls2
	Qt6::Multimedia
	Qt6::WebView
)