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

	Q_INVOKABLE void request();

	[[nodiscard]]
	auto getGranted() const -> bool;

signals:
	void grantedChanged();

private:
	bool isGranted = false;
};
