#pragma once

#include <QJsonObject>
#include <qqmlintegration.h>

class Device
{
	Q_GADGET
	QML_VALUE_TYPE(Device)

	Q_PROPERTY(QString id READ getId)
	Q_PROPERTY(QString name READ getName)
	Q_PROPERTY(QString type READ getType)

public:
	[[nodiscard]]
	static auto fromJson(const QJsonObject &json) -> Device;

	[[nodiscard]]
	auto getId() const -> const QString &;

	[[nodiscard]]
	auto getName() const -> const QString &;

	[[nodiscard]]
	auto getType() const -> const QString &;

private:
	QString id;
	QString name;
	QString type;
};
