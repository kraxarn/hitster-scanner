#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QQmlContext>
#include <QtWebView>

#include "model/devicelistmodel.hpp"
#include "qml/htmlinfo.hpp"
#include "qml/permissionmanager.hpp"
#include "qml/qrcodescanner.hpp"
#include "qml/spotifyapi.hpp"
#include "qml/wordscrambler.hpp"

namespace
{
	void defineTypes()
	{
		qmlRegisterType<HtmlInfo>("HtmlInfo", 1, 0, "HtmlInfo");
		qmlRegisterType<PermissionManager>("PermissionManager", 1, 0, "PermissionManager");
		qmlRegisterType<QrCodeScanner>("QrCodeScanner", 1, 0, "QrCodeScanner");
		qmlRegisterType<SpotifyApi>("SpotifyApi", 1, 0, "SpotifyApi");
		qmlRegisterType<WordScrambler>("WordScrambler", 1, 0, "WordScrambler");
		qmlRegisterType<DeviceListModel>("DeviceListModel", 1, 0, "DeviceListModel");
	}
}

auto main(int argc, char *argv[]) -> int
{
#ifdef Q_OS_ANDROID
	// Workaround for https://bugreports.qt.io/browse/QTBUG-82617
	qputenv("QT_ANDROID_NO_EXIT_CALL", "1");
#endif

	QCoreApplication::setApplicationName(QStringLiteral(APP_NAME));
	QCoreApplication::setApplicationVersion(QStringLiteral(APP_VERSION));
	QCoreApplication::setOrganizationName(QStringLiteral(ORG_NAME));

	QtWebView::initialize();
	const QGuiApplication app(argc, argv);

	QFontDatabase::addApplicationFont(QStringLiteral(":/res/font/regular.ttf"));
	QFontDatabase::addApplicationFont(QStringLiteral(":/res/font/bold.ttf"));
	QFontDatabase::addApplicationFont(QStringLiteral(":/res/font/light.ttf"));

	QGuiApplication::setFont(QFont(QStringLiteral("Brown")));

	QQmlApplicationEngine engine;
	defineTypes();

	QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
		&app, [] { QCoreApplication::exit(-1); },
		Qt::QueuedConnection);

	engine.load(QStringLiteral(":/qml/Main.qml"));

	return QGuiApplication::exec();
}
