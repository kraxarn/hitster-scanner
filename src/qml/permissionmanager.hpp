#pragma once

#include <QObject>
#include <qqmlintegration.h>

class PermissionManager: public QObject
{
	Q_OBJECT
	QML_ELEMENT

	Q_PROPERTY(bool granted READ getGranted NOTIFY grantedChanged)

public:
	explicit PermissionManager(QObject *parent = nullptr);

	Q_INVOKABLE void request() const;

	[[nodiscard]]
	static auto getGranted() -> bool;

signals:
	void grantedChanged();

private:
	[[nodiscard]]
	static auto checkPermission() -> Qt::PermissionStatus;
};
