#pragma once

#include <QJsonObject>
#include <qqmlintegration.h>

class Image
{
	Q_GADGET
	QML_VALUE_TYPE(Image)

	Q_PROPERTY(int width READ getWidth)
	Q_PROPERTY(int height READ getHeight)
	Q_PROPERTY(QUrl url READ getUrl)

public:
	[[nodiscard]]
	static auto fromJson(const QJsonObject &json) -> Image;

	[[nodiscard]]
	auto getWidth() const -> int;

	[[nodiscard]]
	auto getHeight() const -> int;

	[[nodiscard]]
	auto getUrl() const -> const QUrl &;

private:
	int width = 0;
	int height = 0;
	QUrl url;
};
