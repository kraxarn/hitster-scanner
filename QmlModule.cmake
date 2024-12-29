# QML files are in qml/
#qt_policy(SET QTP0004 NEW)

qt_add_qml_module(${PROJECT_NAME}
	URI ${PROJECT_NAME}_app
	VERSION ${PROJECT_VERSION}
	NO_RESOURCE_TARGET_PATH
	QML_FILES
	qml/Main.qml
	qml/Icon.qml
	qml/MenuButton.qml
	qml/HomePage.qml
	qml/HowToPlayPage.qml
	RESOURCES
	res/font/regular.ttf
	res/font/bold.ttf
	res/font/light.ttf
	res/icon/speaker.svg
	res/icon/chevron-left.svg
)