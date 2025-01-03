cmake_minimum_required(VERSION 3.16)
project(hitster VERSION 0.0.1 LANGUAGES CXX)

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
)

target_compile_definitions(${PROJECT_NAME} PRIVATE APP_NAME="${PROJECT_NAME}")
target_compile_definitions(${PROJECT_NAME} PRIVATE APP_VERSION="v${PROJECT_VERSION}")
target_compile_definitions(${PROJECT_NAME} PRIVATE ORG_NAME="${PROJECT_NAME}")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(${PROJECT_NAME} PRIVATE QT_QML_DEBUG)
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
)

if (ANDROID)
	set(DEPENDENCIES
		plugins/iconengines/libplugins_iconengines_qsvgicon_arm64-v8a.so
		plugins/imageformats/libplugins_imageformats_qjpeg_arm64-v8a.so
		plugins/imageformats/libplugins_imageformats_qsvg_arm64-v8a.so
		plugins/multimedia/libplugins_multimedia_androidmediaplugin_arm64-v8a.so
		plugins/networkinformation/libplugins_networkinformation_qandroidnetworkinformation_arm64-v8a.so
		plugins/platforms/libplugins_platforms_qtforandroid_arm64-v8a.so
		plugins/tls/libplugins_tls_qopensslbackend_arm64-v8a.so
		plugins/webview/libplugins_webview_qtwebview_android_arm64-v8a.so
		qml/Qt/labs/qmlmodels/libqml_Qt_labs_qmlmodels_labsmodelsplugin_arm64-v8a.so
		qml/QtMultimedia/libqml_QtMultimedia_quickmultimediaplugin_arm64-v8a.so
		qml/QtQml/Models/libqml_QtQml_Models_modelsplugin_arm64-v8a.so
		qml/QtQml/libqml_QtQml_qmlplugin_arm64-v8a.so
		qml/QtQml/libqml_QtQml_WorkerScript_workerscriptplugin_arm64-v8a.so
		qml/QtQuick/Controls/impl/libqml_QtQuick_Controls_impl_qtquickcontrols2implplugin_arm64-v8a.so
		qml/QtQuick/Controls/Material/impl/libqml_QtQuick_Controls_Material_impl_qtquickcontrols2materialstyleimplplugin_arm64-v8a.so
		qml/QtQuick/Controls/Material/libqml_QtQuick_Controls_Material_qtquickcontrols2materialstyleplugin_arm64-v8a.so
		qml/QtQuick/Controls/libqml_QtQuick_Controls_qtquickcontrols2plugin_arm64-v8a.so
		qml/QtQuick/Effects/libqml_QtQuick_Effects_effectsplugin_arm64-v8a.so
		qml/QtQuick/Layouts/libqml_QtQuick_Layouts_qquicklayoutsplugin_arm64-v8a.so
		qml/QtQuick/libqml_QtQuick_qtquick2plugin_arm64-v8a.so
		qml/QtQuick/Shapes/libqml_QtQuick_Shapes_qmlshapesplugin_arm64-v8a.so
		qml/QtQuick/Templates/libqml_QtQuick_Templates_qtquicktemplates2plugin_arm64-v8a.so
		qml/QtQuick/Window/libqml_QtQuick_Window_quickwindowplugin_arm64-v8a.so
		qml/QtWebView/libqml_QtWebView_qtwebviewquickplugin_arm64-v8a.so
		lib/libQt6Core_arm64-v8a.so
		lib/libQt6Gui_arm64-v8a.so
		lib/libQt6LabsQmlModels_arm64-v8a.so
		lib/libQt6Multimedia_arm64-v8a.so
		lib/libQt6MultimediaQuick_arm64-v8a.so
		lib/libQt6Network_arm64-v8a.so
		lib/libQt6OpenGL_arm64-v8a.so
		lib/libQt6Qml_arm64-v8a.so
		lib/libQt6QmlMeta_arm64-v8a.so
		lib/libQt6QmlModels_arm64-v8a.so
		lib/libQt6QmlWorkerScript_arm64-v8a.so
		lib/libQt6Quick_arm64-v8a.so
		lib/libQt6QuickControls2_arm64-v8a.so
		lib/libQt6QuickControls2Impl_arm64-v8a.so
		lib/libQt6QuickControls2Material_arm64-v8a.so
		lib/libQt6QuickControls2MaterialStyleImpl_arm64-v8a.so
		lib/libQt6QuickEffects_arm64-v8a.so
		lib/libQt6QuickLayouts_arm64-v8a.so
		lib/libQt6QuickShapes_arm64-v8a.so
		lib/libQt6QuickTemplates2_arm64-v8a.so
		lib/libQt6Svg_arm64-v8a.so
		lib/libQt6WebView_arm64-v8a.so
		lib/libQt6WebViewQuick_arm64-v8a.so
	)
	# Deprecated, but ffmpeg backend adds ~15 mb and not really used
	set_target_properties(${PROJECT_NAME} PROPERTIES
		QT_ENABLE_VERBOSE_DEPLOYMENT TRUE
		QT_DEFAULT_MEDIA_BACKEND "android"
		QT_ANDROID_DEPLOYMENT_DEPENDENCIES "${DEPENDENCIES}"
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