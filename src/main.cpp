#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QQmlContext>

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

	QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
		&app, [] { QCoreApplication::exit(-1); },
		Qt::QueuedConnection);

	engine.loadFromModule(QStringLiteral("%1_app").arg(QStringLiteral(APP_NAME)), "Main");

	return QGuiApplication::exec();
}
