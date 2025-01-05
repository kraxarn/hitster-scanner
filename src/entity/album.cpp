#include "entity/album.hpp"

#include <QJsonArray>

auto Album::fromJson(const QJsonObject &json) -> Album
{
	Album album;

	album.name = json[QStringLiteral("name")].toString();

	const auto images = json[QStringLiteral("images")].toArray();
	album.images.reserve(images.size());

	for (const auto image: images)
	{
		album.images.push_back(Image::fromJson(image.toObject()));
	}

	return album;
}

auto Album::getName() const -> const QString &
{
	return name;
}

auto Album::getImages() const -> const QList<Image> &
{
	return images;
}
