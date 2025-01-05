#pragma once

#include "entity/image.hpp"

#include <qqmlintegration.h>

class Album
{
	Q_GADGET
	QML_VALUE_TYPE(Album)

	Q_PROPERTY(QString name READ getName)
	Q_PROPERTY(QList<Image> images READ getImages)

public:
	static auto fromJson(const QJsonObject &json) -> Album;

	[[nodiscard]]
	auto getName() const -> const QString &;

	[[nodiscard]]
	auto getImages() const -> const QList<Image> &;

private:
	QString name;
	QList<Image> images;
};
