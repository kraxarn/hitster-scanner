#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QQmlContext>

#include "qml/htmlinfo.hpp"
#include "qml/permissionmanager.hpp"

namespace
{
	void defineTypes()
	{
		qmlRegisterType<HtmlInfo>("HtmlInfo", 1, 0, "HtmlInfo");
		qmlRegisterType<PermissionManager>("PermissionManager", 1, 0, "PermissionManager");
	}
}

auto main(int argc, char *argv[]) -> int
{
	QCoreApplication::setApplicationName(QStringLiteral(APP_NAME));
	QCoreApplication::setApplicationVersion(QStringLiteral(APP_VERSION));
	QCoreApplication::setOrganizationName(QStringLiteral(ORG_NAME));

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
