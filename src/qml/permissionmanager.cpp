#include "qml/permissionmanager.hpp"

#include <QGuiApplication>

#if QT_CONFIG(permissions)
#include <QPermission>
#endif

PermissionManager::PermissionManager(QObject *parent)
	: QObject(parent)
{
}

void PermissionManager::request() const
{
#if QT_CONFIG(permissions)
	if (checkPermission() == Qt::PermissionStatus::Undetermined)
	{
		qApp->requestPermission(QCameraPermission{},
			this, &PermissionManager::request);
	}
#endif
}

auto PermissionManager::checkPermission() -> Qt::PermissionStatus
{
#if QT_CONFIG(permissions)
	const QPermission permission = QCameraPermission();
	return qApp->checkPermission(permission);
#else
	return Qt::PermissionStatus::Granted;
#endif
}

auto PermissionManager::getGranted() -> bool
{
	return checkPermission() == Qt::PermissionStatus::Granted;
}
