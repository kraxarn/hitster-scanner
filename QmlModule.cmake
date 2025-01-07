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
	qml/HtmlInfoPage.qml
	qml/ScanPage.qml
	qml/Logo.qml
	qml/LoginPage.qml
	qml/AuthPage.qml
	qml/TrackDrawer.qml
	qml/DeviceButton.qml
	RESOURCES
	res/font/regular.ttf
	res/font/bold.ttf
	res/font/light.ttf
	res/icon/speaker.svg
	res/icon/chevron-left.svg
	res/icon/web.svg
	res/icon/flash.svg
	res/icon/flash-off.svg
	res/icon/eye.svg
	res/icon/eye-off.svg
	res/icon/cellphone.svg
	res/icon/laptop.svg
	res/icon/television.svg
)