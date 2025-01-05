#include "entity/image.hpp"

auto Image::fromJson(const QJsonObject &json) -> Image
{
	Image image;

	image.width = json.value(QStringLiteral("width")).toInt();
	image.height = json.value(QStringLiteral("height")).toInt();
	image.url = QUrl(json.value(QStringLiteral("url")).toString());

	return image;
}

auto Image::getWidth() const -> int
{
	return width;
}

auto Image::getHeight() const -> int
{
	return height;
}

auto Image::getUrl() const -> const QUrl &
{
	return url;
}
