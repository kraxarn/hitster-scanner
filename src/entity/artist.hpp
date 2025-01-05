#pragma once

#include <QObject>
#include <qqmlintegration.h>

class Artist
{
	Q_GADGET
	QML_VALUE_TYPE(Artist)

	Q_PROPERTY(QString name READ getName)

public:
	static auto fromJson(const QJsonObject &json) -> Artist;

	[[nodiscard]]
	auto getName() const -> const QString &;

private:
	QString name;
};
