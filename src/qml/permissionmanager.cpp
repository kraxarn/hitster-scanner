#include "qml/permissionmanager.hpp"

#include <QGuiApplication>

#if QT_CONFIG(permissions)
#include <QPermission>
#endif

PermissionManager::PermissionManager(QObject *parent)
	: QObject(parent)
{
}

void PermissionManager::request()
{
#if QT_CONFIG(permissions)
	const QPermission permission = QCameraPermission();
	switch (qApp->checkPermission(permission))
	{
		case Qt::PermissionStatus::Undetermined:
			qApp->requestPermission(permission, this, &PermissionManager::request);
			break;

		case Qt::PermissionStatus::Granted:
			isGranted = true;
			emit grantedChanged();
			break;

		case Qt::PermissionStatus::Denied:
			isGranted = false;
			emit grantedChanged();
			break;
	}
#else
	isGranted = true;
	emit grantedChanged();
#endif
}

auto PermissionManager::getGranted() const -> bool
{
	return isGranted;
}
