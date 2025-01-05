#include "entity/artist.hpp"

#include <QJsonObject>

auto Artist::fromJson(const QJsonObject &json) -> Artist
{
	Artist artist;

	artist.name = json[QStringLiteral("name")].toString();

	return artist;
}

auto Artist::getName() const -> const QString &
{
	return name;
}
